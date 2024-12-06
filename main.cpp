#include <iostream>

int main()
{
  const int HEIGHT = 20;
  const int WIDTH = 20;

  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      float normalizedX = (float)x / (WIDTH - 1) - 0.5f;
      float normalizedY = (float)y / (HEIGHT - 1) - 0.5f;

      if (normalizedX * normalizedX + normalizedY * normalizedY < 0.5f * 0.5f)
      {
        std::cout << "  ";
        continue;
      }
      std::cout << "██";
    }
    std::cout << std::endl;
  }
}
