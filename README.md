# CS241-Final-Project
#
# Authors: Jesse Cruz, Toby Otto, Alim Wilkins
#
# Summary
# --------------------------------------------
# The basic concept of our project is to input
# data in the form of corpus sheets, to then
# use a Markov model to generate a new
# corpus sheet based off of our sample
# files.
# 
# File Descriptions
# --------------------------------------------
# 3 files; read.c, music.c, driver.c
#
# read.c - Attempts to read in from a file
# 	   and create an array of strings
#          each of which represent a chord
#          in the corpus sheet
#
# music.c - Contains all the structs and
#           and functions that are used to
#           create generated array
#           Specifically, uses a dictionary
#           and list system to map keys
#           and freqs, that are then inputted
#           into the markov model to try and
#           create a new arry of chords
#
# driver.c - Where the main function resides
#            Attempts to get array of chords
#            from read, and then used those
#            with the markov model function
#            chooseChord
#
# Bugs
# --------------------------------------------
# read.c - Having issues separating the \n
#  	   character from actual letters
#
# music.c - having trouble switching our
#           markov model to work with
#           int array
#
#
# driver.c - no actual bugs here, just carried
#            over stuff from other files
#
# Ending Thoughts
# ---------------------------------------------
# Pretty obvious almost everything still contains
# bugs. Our overall ideas for structures and
# our process didn't seem entirely flawed
# we probably just needed more time to debug.
# Additionall, with so much fluctuation over
# how to do the project, we needed to have
# decided on parts of the project plan
# much earlier and not have changed pieces
# part way through.
#