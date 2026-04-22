# Cell And Particle Simulation Engine
Cellular automata simulator/engine written in C++ using the opengl specification.

I will try keep the code as readable and commented as possible so its easy for others to read and understand, but I do plan on having most of the customisations
    for the cellular automata within the application itself.

Please note that I am making no promises that this project
    will be finished.

I have included a similar project I created with raylib previously. This raylib version
    is very different to what I plan on the final version being like, so it includes
    a few bugs and is extremely limited.

I have large plans for this engine, it will allow me to make grid based games in c++ easily,
    and I will include some GUI customisation and a way to save and load different simulations/games
    that have been created using the GUI.


# Engine design
This engine is comprised of two components, the renderer, and the logical side.
    These two parts will communicate by the 
    logical side loading the grid data into the render engines
    grid after all updates have been performed on the grid.

Please note that all Dear ImGui code will be stored within the logical side as that
    needs direct access to most variables for the simulations.

# Render half of the engine
Rendering will work by having a quad that is mapped to each corner of the window,
    then a texture is mapped onto this quad. This texture
    will be the array of updated values of the simulation from the previous frame,
    then it will be displayed onto the window.

# Logical half of engine
There will be a main data structure to hold the grid. In every frame, each cell in the
    grid will be updated depending on its properties.
    For example:
        A cell might have an ID of 1, which corresponds to sand, then when it's being
        updated it follows the rules for sand falling ect...
     The logic half then uploads the data to the renderer to be displayed.

