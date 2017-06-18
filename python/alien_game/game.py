import sys
import pygame
from time import sleep
from alien import Alien
from bullet import Bullet
from button import Button
from game_stats import GameStats
from pygame.sprite import Group
from settings import Settings
from ship import Ship

class Game():
    """
    The monolithic game object
    """
    def __init__(self, ai_settings, screen):
        self.__ai_settings = ai_settings
        self.__screen = screen

        # Create an instance to store game statistics
        self.__stats = GameStats(self.__ai_settings)

        # Make a ship, a group of bullets, and a group of aliens.
        self.__ship = Ship(self.__ai_settings, self.__screen)
        self.__bullets = Group()
        self.__aliens = Group()

        # Make the Play button
        self.__play_button = Button(ai_settings, screen, "Play")

        # Create the fleet of aliens
        self.__create_fleet()

    def run_loop(self):
        while True:
            self.__check_events()

            if self.__stats.game_active:
                self.__ship.update()
                self.__update_aliens()
                self.__update_bullets()

            self.__update_screen()
            self.__handle_collision()
            self.__check_aliens_bottom()

    def __check_events(self):
        """Respond to keypresses and mouse events."""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self.__check_keydown_events(event)
            elif event.type == pygame.KEYUP:
                self.__check_keyup_events(event)
            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouse_x, mouse_y = pygame.mouse.get_pos()
                self.__check_play_button(mouse_x, mouse_y)

    def __check_keydown_events(self, event):
        """Respond to keypresses."""
        if event.key == pygame.K_RIGHT:
            self.__ship.moving_right = True
        elif event.key == pygame.K_LEFT:
            self.__ship.moving_left = True
        elif event.key == pygame.K_SPACE:
            self.__fire_bullet()
        elif event.key == pygame.K_q:
            sys.exit()

    def __check_keyup_events(self, event):
        """Respond to key releases."""
        if event.key == pygame.K_RIGHT:
            self.__ship.moving_right = False
        elif event.key == pygame.K_LEFT:
            self.__ship.moving_left = False

    def __check_play_button(self, mouse_x, mouse_y):
        """Start a new game when the player clicks Play."""
        button_clicked = self.__play_button.rect.collidepoint(mouse_x, mouse_y)
        if button_clicked and not self.__stats.game_active:
            # Reset the game settings
            self.__ai_settings.initialize_dynamic_settings()

            # Hide the mouse
            pygame.mouse.set_visible(False)

            # Reset the game statistics
            self.__stats.reset_stats()
            self.__stats.game_active = True

            # Empty the list of aliens and bullets.
            self.__aliens.empty()
            self.__bullets.empty()

            # Create a new fleet and center the ship.
            self.__create_fleet()
            self.__ship.center_ship()

    def __update_screen(self):
        """Update images on the screen and flip to the new screen."""
        # Redraw the screen during each pass through the loop
        self.__screen.fill(self.__ai_settings.bg_color)

        # Redraw all bullets behind ship and aliens.
        for bullet in self.__bullets.sprites():
            bullet.draw_bullet()

        self.__ship.blitme()
        self.__aliens.draw(self.__screen)

        # Draw the play button if the game is inactive.
        if not self.__stats.game_active:
            self.__play_button.draw_button()

        # Make the most recently drawn screen visible
        pygame.display.flip()

    def __fire_bullet(self):
        """Fire a bullet if limit has not reached yet."""
        if len(self.__bullets) < self.__ai_settings.bullets_allowed:
            new_bullet = Bullet(self.__ai_settings, self.__screen,
                self.__ship)
            self.__bullets.add(new_bullet)

    def __update_bullets(self):
        """Update position of bullets and get rid of old bullets."""
        # Update bullet positions.
        self.__bullets.update()

        # Get rid of bullets that have disappeared.
        for bullet in self.__bullets.copy():
            if bullet.rect.bottom <= 0:
                self.__bullets.remove(bullet)

    def __get_number_aliens_x(self, ai_settings, alien_width):
        """Determine the number of aliens that fit in a row."""
        available_space_x = ai_settings.screen_width - 2 * alien_width
        number_aliens_x = int(available_space_x / (2 * alien_width))
        return number_aliens_x

    def __get_number_rows(self, ai_settings, ship_height, alien_height):
        """
        Determine the number of rows of aliens that fit on the screen.
        """
        available_space_y = (ai_settings.screen_height -
            (3 * alien_height) - ship_height)
        number_rows = int(available_space_y / (2 * alien_height))
        return number_rows

    def __create_alien(self, alien_number, row_number):
        """
        Create an alien and place it in the row.
        """
        alien = Alien(self.__ai_settings, self.__screen)
        alien_width = alien.rect.width
        alien.x = alien_width + 2 * alien_width * alien_number
        alien.rect.x = alien.x
        alien.rect.y = alien.rect.height + (2 * alien.rect.height
            * row_number)
        self.__aliens.add(alien)

    def __create_fleet(self):
        """Create a full fleet of aliens."""
        # Create an alien and find the number of aliens in a row.
        # Spacing between each alien is equal to one alien width.
        alien = Alien(self.__ai_settings, self.__screen)
        number_aliens_x = self.__get_number_aliens_x(self.__ai_settings,
            alien.rect.width)
        number_rows = self.__get_number_rows(self.__ai_settings,
            self.__ship.rect.height, alien.rect.height);

        # Create the fleet of aliens.
        for row_number in range(number_rows):
            for alien_number in range(number_aliens_x):
                self.__create_alien(alien_number, row_number)

    def __check_fleet_edges(self):
        """Respond appropriately if any aliens have reached an edge."""
        for alien in self.__aliens.sprites():
            if alien.check_edges():
                self.__change_fleet_direction()
                break

    def __change_fleet_direction(self):
        """Drop the entire fleet and change the fleet's direction."""
        for alien in self.__aliens.sprites():
            alien.rect.y += self.__ai_settings.fleet_drop_speed
        self.__ai_settings.fleet_direction *= -1

    def __update_aliens(self):
        """
        Check if the fleet is at an edge,
        and then update the positions of all aliens in the fleet.
        """
        self.__check_fleet_edges()
        self.__aliens.update()

    def __check_aliens_bottom(self):
        """
        Check if any aliens have reached the bottom of the screen.
        """
        screen_rect = self.__screen.get_rect()
        for alien in self.__aliens.sprites():
            if alien.rect.bottom >= screen_rect.bottom:
                # Treat this the same as if thes hip got hit
                self.__ship_hit()
                break

    def __handle_collision(self):
        # Look for alien-ship collisions.
        if pygame.sprite.spritecollideany(self.__ship, self.__aliens):
            self.__ship_hit()

        # Remove any bullets and aliens that have colliede.
        collisions = pygame.sprite.groupcollide(self.__bullets,
            self.__aliens, True, True)
        if len(self.__aliens) == 0:
            # Destroy existing bullets and create new fleet.
            self.__bullets.empty()
            self.__ai_settings.increase_speed()
            self.__create_fleet()

    def __ship_hit(self):
        """Respond to ship being hit by alien."""
        if self.__stats.ships_left > 1:
            # Decrement ships_left
            self.__stats.ships_left -= 1
        else:
            self.__stats.game_active = False
            pygame.mouse.set_visible(True)

        # Empty the list of aliens and bullets
        self.__aliens.empty()
        self.__bullets.empty()

        # Create a new fleet and center the ship
        self.__create_fleet()
        self.__ship.center_ship()

        # Pause.
        sleep(0.5)

        print("Hit! ships left = %d, aliens = %d" % (
            self.__stats.ships_left, len(self.__aliens)))
