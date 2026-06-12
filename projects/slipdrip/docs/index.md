---
layout: default
title: "Project 2 Proposal"
---
# Project 2 Documentation: Slip Drip

# What is SlipDrip?

## Overview
Our goal was to create a custom CNC machine that allows the user to create highly geometric designs using pigmented and non-pigmented slip dripped from an extruder. We accomplished this goal by modifying a Creality Ender 3, and removing everything except for the axes, and connecting it to a Stepdance board. Through the Stepdance board, a user is able to define the extrusion rate, the height of the extruder, the location of the extruder head, and the calibration of the machine. To drip slip from the extruder, we used a syringe and a pushing mechanism to allow for slip extrusion.

## Mechanism Design

To start, we had to remove all the extra components of the Ender so that we would have the most space to modify the mechanism. From there, the main focus was experimenting with different designs for how to best extrude slip from where the former extrusion head had been.

Timeline:
1. Instructor Example
We started off by using the instructor model, understanding its features, and figuring out how we could modify it into a design similar to one made by [Constantijn](https://www.youtube.com/watch?v=Q3A4NqTPOYY).
![Instructor Model](assets/instructormodel.jpeg)
2. Syringe holder and pusher
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

## Material Testing

## Interacting with SlipDrip

## Challenges

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