# Release and Versioning 

## Branching 
- All non-documentation changes should be done in branch from main.
- Name branches as follows:
  - `bugfix-<name>` for bugfixes
  - `cleanup-<name>` for refactors, cleanups, etc that don't introduce or remove functionality
  - `feature-<name>` for changes that introduce or remove functionality, including tests

## Versioning format
All releases should be done on github with tagging. Each release should have a short description of what it involves, a bulleted list of significant changes, and a release artefact (presently just GIFs demonstrating progress, but eventually binaries for people to download).

The tag format is `v{major}.{minor}`, where major versions represent significant functionality changes, and minors represent smaller parts of new functionality. 
Typically, a handful of branches should be released as a minor version, and then several minor versions should be released as a major version.

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

