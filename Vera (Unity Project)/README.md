# Summary

This collection of files is from a game I co-built in Unity in 2014 as a senior project working with 2 other developers and 2 other artists to build a 3D, networked open-world game where players could craft structures for survival and protection. Think Fortnite with a survival twist instead of a combat emphasis. 

The selection of 5 files I chose should illustrate a working knowledge of object-oriented programming concepts and the C# language, as utilized in a real game. The purpose of these files all together was to implement the resource gathering logic that would be utilized when we tried to chop a tree into wood or mine ore with a pickaxe. I accomplished this by creating an abstract class called ResourceGatherCollider which is use to implement the concrete classes AxeCollider and PickAxeCollider. The resource that was collected is represented by either the Tree or Ore class, which both inherit from parent class Resource. In a real scene in Unity these would all be attackhd to the individual GameObjects they represent - the axe, pickaxe, trees and ore deposits.

# Source

Full Source Code on [Github](https://github.com/kaizerroll/Vera)

The code for this game mostly lives in the /Assets/Scripts/ folder

> Note: the examples shown here have been heavily commented to explain functionality

# File strucure

- AxeCollider.cs - a concrete class that implements ResourceGatherCollider. Implements the functions GetResourceTag and CanDestroyBuilding. In hindsight this looks could be implemented with basic class variables, instead of getter functions, but I left it as is to illustrate a real example of code.

- Ore.cs - a MonoBheavior attached to any Ore GameObject in the scene

- PickAxeCollider.cs - another concrete implementation of ResourceGatherCollider, for collecting Ore

- Resource.cs - The parent class for resources (Ore and Tree) that implements the Gather function, which will be called by ResourceGatherCollider whenever a resource is being gathered.

- ResourceGatherCollider.cs - the abstract class that PickAxeCollider and AxeCollider inherit from. Implements the logic to play the 'attack' animation on player click, and implements OnTriggerEnter, which will be called by Unity anytime the GameObject's mesh collides with another object in the scene.

- Tree.cs - another object representing a resource, like Ore

# Output

This is a [trailer for the game](https://vimeo.com/95832567)

