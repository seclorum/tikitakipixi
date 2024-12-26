import Cocoa

class ViewController: NSViewController {

    var loupeWindow: NSWindow!
    var capturedImageView: NSImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Create a separate window for the loupe
        loupeWindow = NSWindow(contentRect: NSMakeRect(0, 0, 200, 200),
                               styleMask: [.borderless, .titled],
                               backing: .buffered,
                               defer: false)
        loupeWindow.isOpaque = false
        loupeWindow.backgroundColor = NSColor.clear
        loupeWindow.level = .floating
        
        // Create an image view to display the captured area
        capturedImageView = NSImageView(frame: loupeWindow.contentView!.bounds)
        capturedImageView.autoresizingMask = [.width, .height]
        loupeWindow.contentView?.addSubview(capturedImageView)
    }

    override func mouseDragged(with event: NSEvent) {
        let location = event.locationInWindow
        updateLoupe(at: location)
    }
    
    func updateLoupe(at location: NSPoint) {
        // Convert the location to the global screen coordinates
        let screenLocation = NSEvent.mouseLocation
        
        // Capture the screen area at the mouse location
        let captureRect = CGRect(x: screenLocation.x - 50, y: screenLocation.y + 50, width: 100, height: 100)
        if let imageRef = CGWindowListCreateImage(captureRect, .optionOnScreenOnly, kCGNullWindowID, [.bestResolution]) {
            let image = NSImage(cgImage: imageRef, size: NSSize(width: captureRect.width, height: captureRect.height))
            capturedImageView.image = image
        }
        
        // Update the loupe window position
        let windowLocation = NSPoint(x: location.x - 100, y: location.y - 100)
        loupeWindow.setFrameOrigin(windowLocation)
        loupeWindow.makeKeyAndOrderFront(nil)
    }
}
