#pragma once
 
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
 
#include "LoupeComponent.h"

//==============================================================================
class MainComponent : public juce::Component
{
public:
    MainComponent()
    {
        setSize (600, 400);
        addAndMakeVisible(loupeComponent);
    }

    ~MainComponent() override {}

    void paint (juce::Graphics&) override {}

    void resized() override
    {
        loupeComponent.setBounds(0, 0, 200, 200); // Position the loupe component
    }

private:
    LoupeComponent loupeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
