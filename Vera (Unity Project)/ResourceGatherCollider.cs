using UnityEngine;
using System;

public abstract class ResourceGatherCollider : MonoBehaviour
{
	// the damage each swing causes to the resource
	public int DamageValue = 50;
	// number of hits each swing creates (defaults to 1)
	public int numHitsOnSwing = 1;
	// cooldown until next swing, in ms
	public int coolDownMilli = 1000;
	// represents the attack cooldown as a TimeSpan
	private TimeSpan attackCooldown;
	// the DateTime representing the last attack
	private DateTime? lastAttack;
	// represents the resource gathering cooldown as a TimeSpan
	private TimeSpan delayCoolDown;
	// represents the time since a building has been built
	private DateTime? buildDelay;
	// Represents the Build class we use for building structures
	private Build b;
	// Represents the users inventory
	private Inventory inventory;
	// represents the Animator class on the Character
	public Animator animator;
	
	// initialize attack and resource gathering cooldowns
	void Start () {
		attackCooldown = new TimeSpan(0, 0, 0, 0, coolDownMilli);
		delayCoolDown = new TimeSpan(0, 0, 0, 0, 500);
	}
	
	// runs on every frame
	void Update () {
		b = Spawn.GetCurrentPlayer().GetComponent<Build>();
		inventory = Spawn.GetCurrentPlayer().GetComponent<Inventory>();

		// if Builder currently is holding a building, set buildDelay to now
		if (b.HasBuilding()) 
		{
			buildDelay = DateTime.Now;
		}
		
		// if Now - buildDelay exceeds the cooldown, we can enter the 'firing' code
		if ((DateTime.Now - buildDelay) > delayCoolDown || buildDelay == null) 
		{
			// if user has clicked main attack button, and the atackCooldown is passed
			if (Input.GetButtonDown("Fire1") && (lastAttack == null || (DateTime.Now - lastAttack) >= attackCooldown))
			{
				// null check animator, and if so, set off the Attack animation (swing the tool)
				if (animator)
				{
					animator.SetTrigger("Attack");
				}

				lastAttack = DateTime.Now;
			}
		}
	}

	/// <summary>
	/// Gets the tag that corresponds to the resource that this weapon can gather.
	/// </summary>
	/// <returns>The tag of the resource.</returns>
	protected abstract string GetResourceTag();

	/// <summary>
	/// Returns true if this weapon can destroy buildings.
	/// </summary>
	/// <returns>True if this weapon can destroy buildings.</returns>
	protected abstract bool CanDestroyBuilding();
	
	// when the tool collides with another object
	void OnTriggerEnter(Collider other) {
		// if attack animation is playing
		if (animator && animator.GetCurrentAnimatorStateInfo(0).IsName("Attack")) {
			// and the object's tag matches the resource we can gather
			if (other.gameObject.tag == GetResourceTag())
			{
				//play relevant resource gathering sound on every hit
				gameObject.GetComponent<AudioSource>().Play();
				// get the Resource component of the other object
				Resource resource = other.gameObject.GetComponent<Resource>();
				// attempt to gather the resource
				int gatherCount = resource.Gather(numHitsOnSwing);
				// if you did gather something
				if (gatherCount > 0)
				{
					// depending on the type of the resource, we call a different function on the inventory
					if (resource is Tree) 
					{
						inventory.AddWood(gatherCount);
					}
					else if (resource is Ore) 
					{
						inventory.AddOre(gatherCount);
					} 
					// sanity check the resource
					else
					{
						Debug.LogError("No such resource");
					}
				}

			}
			// if what we're trying to gather is a Building and we can destroy buildings
			else if (other.gameObject.tag == "Building" && CanDestroyBuilding())
			{
				//play relevant resource gathering sound on every hit
				gameObject.GetComponent<AudioSource>().Play ();
				Health buildingHealth = other.gameObject.GetComponent<Health> ();
				// call Damage on the building's Health
				if (buildingHealth != null) {
					buildingHealth.Damage(DamageValue);
				}
			}
		}
	}
}