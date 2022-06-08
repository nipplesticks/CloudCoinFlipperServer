#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

struct RandPacket
{
  unsigned short min;
  unsigned short max;
};
struct ResPacket
{
  unsigned short value;
};

int main()
{
  // Server
  sf::TcpListener listener;

  if (listener.listen(4444) != sf::Socket::Done)
  {
    std::cout << "Cannot listen!\n";
    return 1;
  }

  sf::TcpSocket client;
  if (listener.accept(client) != sf::Socket::Done)
  {
    std::cout << "Cannot accept client!\n";
    return 1;
  }

  RandPacket rnd{};
  ResPacket res{};

  int idx = 0;
  while (true)
  {
    if (idx > 5)
    {
      client.disconnect();
      break;
    }
    size_t dataRecieved = 0;

    if (client.receive(&rnd, sizeof(rnd), dataRecieved) != sf::Socket::Done)
    {
      std::cout << "Failed to receive!\n";
      idx++;
      continue;
    }

    res.value = rand() % (rnd.max + 1) + rnd.min;

    if (client.send(&res, sizeof(res)) != sf::Socket::Done)
    {
      std::cout << "Failed to send!\n";
      continue;
    }

    std::cout << "Value sent: " << res.value << std::endl;
  }

  return 0;
}