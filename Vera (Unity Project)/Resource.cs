using UnityEngine;
using System.Collections;

public class Resource : MonoBehaviour {

	/// <summary>
	/// The number of axe or pickaxe hits it takes to gather.
	/// </summary>
	protected int hits;

	/// <summary>
	/// The number of units of the resource per gather.
	/// </summary>
	protected int gatherCount;

	/// <summary>
	/// Attempts to gather a resource.
	/// </summary>
	/// <param name="numHits">The number of axe or pickaxe hits.</param>
	/// <returns>The number of units gathered.</returns>
	public int Gather(int numHits)
	{
		if (numHits <= 0)
			throw new UnityException("numHits must be positive");

		// decrement local hits counter
		hits -= numHits;
		// if hits reaches 0, destroy the object
		if (hits <= 0)
		{
			hits = 0;
			Utility.DestroyHelper(gameObject);
			return gatherCount;
		}
		else
			return 0;
	}
}
