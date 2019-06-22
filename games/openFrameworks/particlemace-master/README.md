# particlemacearcade
Working on the arcade version of PM.

This has been updated to openframeworks 0.9.8

It uses ofxJoystick in place of the old gamepad library
https://github.com/Lacty/ofxJoystick

When installing it on a new machine, you'll need to install the vc_redist and k_lite codec pack in the install folder.

For Vector display, use this repo: https://github.com/andymasteroffish/ofxVst



## Linux

Once the framework--well,--works we must prepare Particle Mace. Start by downloading `particlemace.zip` from this repository, or get it from @andymakes. Extract this zip file somewhere handy. 

Before we can compile remove the folder `src/system_specific_mac` from wherever you saved Particle Mace. 

You are now ready to compile. Make sure to substitute `path/to/particlemace` with the path to wherever you found it handy to extract Particle Mace. 
```
cp -r path/to/particlemace OF_0.9.8/apps/myApps
cd OF_0.9.8/apps/myApps/particlemace
make
```

The final step (this may apply to more than just linux) is to move `particlemace/shaders` into `particlemace/data` and then `particlemace/data`into `particlemace/bin`. If you havent closed the terminal you just used to run `make` run these commands,
```
mv shaders/ data/
mv data/ bin/
```

You should be able to run the game with `make RunRelease`, or executing the script in `particlemace/bin`