# cell Simulator
    Cellular automata simulator/engine written in C++ using the opengl specification.

    this project is a learning tool for the very basics of opengl.

    I will try keep the code as readable and commented as possible so its easy
    for others to read and understand, but i do plan on having most of the customisations
    for the cellular automata withing the application itself.

    please note that i am making no promises that this project
    will be finished

    i have included a similar project i created with raylib previously. This raylib version
    is very different to what i plan on the final version being like, so it includes
    a few bugs and is extremley limited.


# Engine design
    This engine is comprised of two components, The renderer, and the Logical side.
    These two parts will communicate by the 
    logical side loading the grid data into the render engines
    grid after all updates have been preformed on the grid

    note that all Dear imGui code will be stored withing the logical side as that
    needs direct access to most variables for the simulations

# Render half of the engine
    rendering will work by having a quad that is mapped to each corner of the window,
    then a texture is mapped onto this quad, this texture
    will be the array of updated values of the simulation form the previous frame,
    then it will be displayed onto the window

# Logical half of engine
    there will be a main data structure to hold the grid, every frame each cell in the
    grid will be updated depending on its properties,
    for example:
        a cell might have an ID of 1, which corresponds to sand, then when its being
        updated it follows the rules for sands falling rules ect...

