# PROBLEMS
- ViewConfig construction requires SFML classes
- Buttons shouldn't have texture and text by default
- Button text & texture shouldn't overlap
- Managers can be bypassed by user -> lifetime issues for user
- No way for user to acces models (solve by making models hold references)
- Cells in Grid may be empty/null

# Future constraints
- 1 texture for all instances, can't change it at runtime (is that even a problem?)
- Static entries of managers cloud memory (only a problem for big projects)