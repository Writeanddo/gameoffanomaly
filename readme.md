# Submission for [Game off 2024](https://itch.io/jam/game-off-2024) jam.

Notes on contribution:
- Uses Unreal 5.4.4
- Before cloning, make sure to have [git-lfs installed](https://git-lfs.com/)
- Content folders description:
- - `Actors/`: Contains all the actors that are used in the game, like player, enemies, etc.
- - `Assets/`: Art assets, like textures, materials, meshes, etc.
- - `Input/`: Contains all the input actions and mappings.
- - `Maps/`: Contains all the maps of the game.
- - - `Release`: Contains maps to be shipped with the game.
- - - `SandBox`: Contains maps for testing and development.
- - `UI/`: Contains all the UI assets, like widgets, etc.
- - `Flow/`: What controls game flow, like game modes, game states, etc.
- - `Sound/`: Contains all the sound assets.
- Since file locking is not supported by git-lfs, make sure to communicate with the team before working on a file.
- Watch what you commit - don't commit any unnecessary files.
- If there's potential for a merge conflict for a particular asset - make a copy of the asset and work on that, then merge the changes manually.
- DONT USE BP STRUCTS 
- Don`t push to main branch, create a new branch and make a pull request.
- 