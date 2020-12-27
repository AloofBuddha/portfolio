# Summary

Some C++ files that were used in creating a ray tracer for a Computer Graphics class, as I wanted to show some C++ as I know it's used heavily in game development scenarios. I included the rayScene, raySphere and rayPointLight classes as together they can illustrate how a single scene is constructed, with at least one light source and one geometric object. All files have been heavily commented so you can understand what's happening. Note, there are instances where global variables are used that are outside the scope of the provided examples. Whenever a variable is used, such as 'group' or 'background' in rayScene.cpp, such variables were defined within the main.cpp file.

# Source

I cannot provide the full source on this as it was for an assignment, and I don't beleive the professor would appreciate me publishing a completed version as a public repo.

# File strucure

- rayScene.cpp - implements GetRay and GetColor functionality that first creates a Ray3D object that represents a ray cast from the camera to a pixel on the screen. GetColor is then used to get the color of that pixel given any objects it reflects off of (or passes through, in the case of transparency). 

- raySphere.cpp - implements the intersect functionality to determine if a given ray intersects this sphere

- rayPointLight.cpp - represents a point light which gives off diffuse and specular light


# Output

See the output tab for example shots taken from the fully running raytracer
