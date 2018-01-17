// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numer = atoi(strtok(fraction, "/"));
    int denom = atoi(strtok(NULL, "/"));
    int duration;

    switch (denom)
    {
        case 1:
            duration = numer * 8;
            break;
        case 2:
            duration = numer * 4;
            break;
        case 4:
            duration = numer * 2;
            break;
        case 8:
            duration = numer;
            break;
    }

    return duration;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int freq;
    string octave[] = { "C", "C#", "D", "D#", "E", "F",
                        "F#", "G", "G#", "A", "A#", "B"
                      };


    char key[3] = { note[0], '\0', '\0' };
    int oct;
    if (strlen(note) == 3)
    {
        // the note has accidental
        key[1] = note[1];
        oct = atoi(&note[2]);
        // transfer #(sharp) to b(flat)
        if (key[1] == 'b')
        {
            if (key[0] == 'A')
            {
                key[0] = 'G'; // Ab turns into G#
            }
            else
            {
                key[0]--; // Gb turns into F#
            }
            key[1] = '#';
        }
    }
    else
    {
        oct = atoi(&note[1]);
    }

    // find the distance between key and A
    int index = indexOf(octave, sizeof(octave) / sizeof(string), key);
    int distance = index - 9;

    // frequency of A4 is 440Hz
    freq = roundf(pow(2, (oct - 4)) * 440 * pow(2, distance / 12.0f));

    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return 1;
    }

    return 0;
}

int indexOf(string *s, int length, string find)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(s[i], find) == 0)
        {
            return i;
        }
    }

    return -1;
}