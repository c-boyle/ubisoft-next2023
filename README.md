# Ubisoft Next 2023 (NES Bomberman Clone Challenge)
This repository contains my submission for the Ubisoft Toronto NEXT challenge 2023. The challenge was to create a clone of the [NES classic Bomberman](https://en.wikipedia.org/wiki/Bomberman_(1983_video_game))
with our own fun twists on the game using a simple API provided by Ubisoft. My submission uses randomization to show off the abstract implementation of the game. 
All enemies, blocks, and special bomb types are generated with random abilities, behavior, and detonation logic. 
For example, you may encounter an enemy that uses A* for its pathfinding, gives you bonus score when you destroy it, 
and spawns another enemy upon destruction, or a bomb, or a block, each of which would be randomly generated itself.

# Built with
- C++
- [Ubisoft NEXT API (supports playing sounds, displaying sprites, and getting input)](./NEXT-API/GameTest/App)

# Features
- [Randomized level generation system with tweakable parameters](./NEXT-API/GameTest/MyApp/LevelGenerator.cpp)
- [A* algorithm for optimal AI pathfinding](./NEXT-API/GameTest/MyApp/AStar.cpp)
- [Abstract game logic that supports highly customizable creation of game objects](./NEXT-API/GameTest/MyApp/LevelObject.cpp)
- New enemies, bomb types, and blocks

# What I learned
This challenge was incredibly fun to participate in, as I hadn't worked with C++ much before but enjoy it a lot as a language. An educational focus of mine for this challenge was
to learn more about writing modern C++ code and making effective use of the C++ Standard Library. I felt that I was able to meet my educational goals during this challenge, 
as I made use of smart pointers, the auto keyword, constexpr, and other modern C++ best practices throughout the code.
