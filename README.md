# Raymond Tree Algorithm

## Features

* Yellow (\033[33m) for token holder nodes.

* Green (\033[32m) for the current node (overrides yellow if the current node is the token holder).

* Red (\033[31m) for other nodes in the path.

* Cyan (\033[36m) for connectors (┌, ├, └, │).

* Reset (\033[0m) after each colored element to prevent color bleed.

* : Added ★ before the node ID if it’s the token holder (e.g., ★5).

* : Added (h:<holderval>) after each node ID to show the Raymond algorithm’s state (e.g., 5 (h:3)).

* : Used ┌ for the root node, ├ for non-last children, and └ for last children to enhance the hierarchy. Adjusted the printTreeASCII logic to use ┌ for the root (level 0).

## Example output

![terminal-output](https://i.postimg.cc/s24xyc8j/Screenshot-2025-08-04-161731.png)
