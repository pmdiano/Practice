import sys
import pygame
from game import Game
from settings import Settings

def run_game():
    # Initialize pygame
    pygame.init()

    # Create settings and screen
    ai_settings = Settings()
    screen = pygame.display.set_mode(
        (ai_settings.screen_width, ai_settings.screen_height))
    pygame.display.set_caption("Alien Invasion")

    # Create the game
    game = Game(ai_settings, screen)

    # Start the main loop for the game:
    game.run_loop()

run_game()
