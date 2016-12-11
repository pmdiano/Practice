import sys
import pygame

def run():
    pygame.init()
    screen = pygame.display.set_mode((400, 300))
    pygame.display.set_caption("Game")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                print("Key %c pressed" % event.key)

        screen.fill((126, 192, 238))
        pygame.display.flip()

run()
