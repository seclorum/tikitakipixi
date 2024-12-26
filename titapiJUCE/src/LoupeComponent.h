#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include <ApplicationServices/ApplicationServices.h>

//==============================================================================
class LoupeComponent : public juce::Component, private juce::Timer
{
public:
    LoupeComponent()
    {
        setSize(200, 200);
        startTimer(30); // Update the loupe every 30 milliseconds
    }

    ~LoupeComponent() override {}

    void paint(juce::Graphics& g) override
    {
        if (capturedImage.isValid())
        {
            g.drawImage(capturedImage, getLocalBounds().toFloat());
        }
    }

    void mouseDrag(const juce::MouseEvent& event) override
    {
        auto screenPos = event.getScreenPosition();
        captureScreenArea(screenPos);
    }

private:
    juce::Image capturedImage;

    void timerCallback() override
    {
        repaint();
    }

    void captureScreenArea(juce::Point<int> screenPos)
    {
        int captureWidth = 100;
        int captureHeight = 100;

        CGRect captureRect = CGRectMake(screenPos.x - captureWidth / 2, screenPos.y - captureHeight / 2, captureWidth, captureHeight);

        CGImageRef imageRef = CGWindowListCreateImage(captureRect, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);

        if (imageRef != nullptr)
        {
            // Create a new juce::Image to store the captured data
            juce::Image juceImage(juce::Image::ARGB, captureWidth, captureHeight, true);

            // Copy pixel data from CGImageRef to juce::Image
            juce::Image::BitmapData bitmapData(juceImage, juce::Image::BitmapData::writeOnly);
            CGContextRef context = CGBitmapContextCreate(bitmapData.data,
                                                         captureWidth,
                                                         captureHeight,
                                                         8,
                                                         bitmapData.lineStride,
                                                         CGImageGetColorSpace(imageRef),
                                                         kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);

            CGContextDrawImage(context, CGRectMake(0, 0, captureWidth, captureHeight), imageRef);
            CGContextRelease(context);

            capturedImage = juceImage;

            // Optional: Add a border to the loupe
            juce::Graphics g(capturedImage);
            g.setColour(juce::Colours::red);
            g.drawRect(capturedImage.getBounds(), 2);

            CGImageRelease(imageRef);
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoupeComponent)
};
