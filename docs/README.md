Docs
---
## Upcoming versions / features
Order/priority is loose / not committed; "X" means "any value", "?" means "no idea, but pretty far off".

### Minor versions
- v0.2 - shooting
- v0.3 - win/lose/restart
- v0.4 - animations
- v0.5 - audio 
- v0.6 - Initial level layout with textures I purchased
- v0.7 - Simple start menu with credits and intro animation cinematic
- v? - Level editor 
### Patches
- v0.X.1 - overhaul of physics system to support better collisions and movement
- v0.X.2 - texture scaling to fit screen
- v0.X.3 - WAD loading and saving
- v0.X.4 - Threaded REPL with very simple commands for adding, removing, moving, etc game objects 
- v0.X.5 - Full unit test coverage with gTest
- v0.X.6 - Continuous integration on GitHub
- v0.X.7 - Overhaul Make system so I don't have to recompile everything all the time. 
- v? - Update REPL to a full Python interpreter

## Versioning
Format: "v{major}.{minor}.{patch_number or string}"
- Branching and squashing are done for major tasks. 
- Patch numbers are bumped any time a branch gets merged back into mainline, typically
  when that task doesn't result in new gameplay features. 
    Examples:
    - Refactor that doesn't change functionality, overhaul of some subsystem. 
    - Adding level serialization
    - Implementing an interpreter to run in a second thread for interacting with 
      the engine at runtime. 
- Minor versions should occur with a notable gameplay feature is introduced.
    Examples:
    - Shooting
    - AI waypoints
    - UI menus
- Major versions occur if a significant amount of gameplay has changed and the game is now fundamentally
  different. 
  Examples:
    - Quests have been added 
    - Upgrading and experience points are added
    - Multiple classes and skill trees are added
