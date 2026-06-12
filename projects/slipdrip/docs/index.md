---
layout: default
title: "Project 2 Proposal"
---
# Project 2 Documentation: Slip Drip

# What is SlipDrip?

## Overview
Our goal was to create a custom CNC machine that allows the user to create highly geometric designs using pigmented and non-pigmented slip dripped from an extruder. We accomplished this goal by modifying a Creality Ender 3, and removing everything except for the axes, and connecting it to a Stepdance board. Through the Stepdance board, a user is able to define the extrusion rate, the height of the extruder, the location of the extruder head, and the calibration of the machine. To drip slip from the extruder, we used a syringe and a pushing mechanism to allow for slip extrusion.

## Material Testing

1. Slip Creation
We begun by creating the material that would be extruded out of the syringe, as if the material couldn’t be extruded than designing the mechanism would be useless. Using recycled clay and smashing it into smaller and smaller pieces and then combining with water we created a “mother slip” from which all our other slips would come out from. We knew that it was right when we tested it on a sponge and created nice blobs of slip


[Crushing the Recycled Clay](assets/crushingclay.jpeg)
[Testing On Sponge](assets/slipsponge.jpeg)


2. Pigmented Slip
Following a recipe provided by [The Ceramics Bible](https://www.amazon.com/Ceramics-Bible-Revised-Louisa-Taylor/dp/1797215140/ref=pd_sbs_d_sccl_1_1/141-1527759-0986908?pd_rd_w=jjKfE&content-id=amzn1.sym.aa738fbd-ad05-4d11-aae2-04b598db6305&pf_rd_p=aa738fbd-ad05-4d11-aae2-04b598db6305&pf_rd_r=1V6GF4VKX9VRSJRZJX1C&pd_rd_wg=zmXD8&pd_rd_r=c3bc12e0-6cf4-4827-a001-c66b4e96c542&pd_rd_i=1797215140&psc=1) by Louisa Taylor we created two pigmented slips one with Cobalt Carbonate (Blue) and the other with Copper Carbonate (Green)

[Pigmented Slip Creation](assets/pigmentedslip.jpeg)

3. Consistency of Slip
As this was done over the course of weeks we had to constantly add water or add more slip to make sure that the consistency was right to be extruded.


## Mechanism Design

To start, we had to remove all the extra components of the Ender so that we would have the most space to modify the mechanism. From there, the main focus was experimenting with different designs for how to best extrude slip from where the former extrusion head had been.

Timeline:
1. Instructor Example
We started off by using the instructor model, understanding its features, and figuring out how we could modify it into a design similar to one made by [Constantijn](https://www.youtube.com/watch?v=Q3A4NqTPOYY).

![Instructor Model](assets/instructormodel.jpeg)

3. Syringe holder and pusher
After consulting with Emile and Alejandro, we were able to CAD a simple design that allowed us to use a small syringe to extrude slip. Once it was constructed, however, it became obvious that we would need to accommodate more syringe sizes and a better mechanism to push the plunger.

This was our first version of the extruder.

![Extruder Version 1](assets/extruder_v1.jpeg)

4. Creation of the screw-in
We remembered that we were able to use different sizes of paintbrushes with an AxiDraw, so we consulted with our TA and found that we could implement the same system in our machine. We started with a circle, but were advised to use a triangle, as it allowed more syringe diameters to fit.

6. Slot-in mechanism
Using the same advice from how the syringe is held, we created a triangular slot for the plunger to sit in so that the slip could be dripped effectively.

8. Removal of weight
Our instructor then looked at our design and confirmed that it functioned with the above specifications, but noticed that the entire assembly was too heavy and that the mechanism didn't need to be as large. We replaced the steel rods with aluminum rods and the original lead screw with a 150 mm lead screw.

Skipping over assembly, fitting, and other minor issues, we were able to get our final design working.

![Final Extruder](assets/finalextruder.jpeg)


## Software Design

1. Polar Kinematics Example
2. Linking Everything Together
3. Circle Generation
4. New Interfacing
5. Scaling and Filtering
6. More Interfacing

## Interacting with SlipDrip

After working for awhile refining how we think a user would operate with slip drip we understood that the process was involved and needed more guidance. To solve this we created a list of instructions in order for a user to use the machine. We consulted with our classmates to understand what we might’ve missed and revised. By the end we had the following instructions to use SlipDrip

### Before Powering the System
1. Set Potentiometer 1 to 0 by turning it clockwise.
2. Set Potentiometer 2 to 0 by turning it counterclockwise.
3. Zero the X-axis by moving the extruder to the left-most side of the belt.
4. Zero the Y-axis by moving the print bed to the back of the printer.

[User Interface](assets/controlsystem.jpg)

### Calibrating the Printer
1. Power up the Stepdance board and send the program from your device.
2. Press the red button to send the X and Y axes to the "start" position.
3. Load the slip into the empty syringe until it hits the 7 mL mark.
4. Before inserting the syringe, ensure that the upper platform is around 70% of the height of the lead screw. To tune this height:
   - Press the Blue Button to incrementally raise the platform.
   - Turn Potentiometer 2 clockwise to lower the platform.
5. Fasten the syringe in the upper platform by sliding the end of the plunger into the triangular slit.
6. On the lower platform, tighten the screw clockwise to fix the syringe in place, ensuring that the needle is situated beneath the platform.

### Using the Ceramic Slip-Drip Printer
1. Center your ceramic bisqueware on the bat.
2. To fasten the bat onto the print bed, check these conditions:
   - The round pegs on the bed are aligned with the diagonal inner holes under the bat.
   - The square-shaped pegs sit flush between the grid lines under the bat.
3. Use the Encoder labeled R to set the desired radius of the slip pattern.
4. Use the Encoder labeled Z to adjust the z-axis height so that the syringe needle doesn't crash into the artifact.
5. Carefully turn Potentiometer 1 counterclockwise until the extruder drips.
6. When you are satisfied with the resulting pattern, turn the potentiometer back to 0 to halt the slip extrusion.

[In Operation](assets/inoperation.jpg)


## Artifacts

In the end we we’re able to make multiple artifacts from a range of different clays and different firings of clay

[Example_1](assets/pre-kiln.jpeg)
[Example_2](assets/postkiln1.jpg)
[Example_3](assets/postkiln2.jpg)
[Example_4](assets/postkiln3.jpg)
[Example_5](postalize.jpg)


## Challenges

1. User Interface
2. Slip Consistency
3. Centering
4. Mechanism Accuracy

## Future Prospects

# Retrospective

## Interaction and Interface

### Standard -> Custom 
Does the machine necessitate a novel mechanism (or mechanisms) in any part of its functionality? Does it adapt existing mechanisms

### Walk Up and Use -> Requires Skill / Training 
Would someone need to practice with the machine to use it effectively? Or is the interaction relatively controlled and constrained? What element of risk, if any does the machine introduce?

## Mechanism

### Standard -> Custom 
Does the machine necessitate a novel mechanism (or mechanisms) in any part of its functionality? Does it adapt existing mechanisms

### Underengineered -> Overengineered 
What is the relationship between the amount of engineering complexity and the application? How robust is the mechanism and how many cycles of operation is it likely to withstand? What level of prototype is the mechanism? How might it be improved?

### Tool-like -> Machine-like 
How similar is the machine to an automated fabrication technology versus a manual tool?

## Artifacts

### Refined -> Rough 
What is the degree of craftsmanship of the artifacts?

### Can be produced by other means -> Only feasible with this machine 
Could the artifacts be produced by other means? If so, what would be involved? Does the machine reduce challenges or create new opportunities compared to other workflows for artifact production?

### Manual -> Automatically produced 
How much of the artifact is produced through manual means vs automation? Where is the line drawn?

### Pre-planned -> Determined during fabrication 
To what degree is the design of the artifacts determined/specified in advance of material interaction?