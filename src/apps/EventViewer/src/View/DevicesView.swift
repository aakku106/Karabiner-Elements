import SwiftUI

struct DevicesView: View {
  @ObservedObject var devicesJsonString = DevicesJsonString.shared

  var body: some View {
    VStack(alignment: .leading, spacing: 12.0) {
      GroupBox(label: Text("Devices")) {
        VStack(alignment: .leading, spacing: 12.0) {
          Button(
            action: {
              let pboard = NSPasteboard.general
              pboard.clearContents()
              pboard.writeObjects([devicesJsonString.text as NSString])
            },
            label: {
              Label("Copy to pasteboard", systemImage: "arrow.right.doc.on.clipboard")
            })

          ScrollView {
            HStack {
              VStack(alignment: .leading) {
                Text(devicesJsonString.text)
                  .lineLimit(nil)
                  .font(.custom("Menlo", size: 11.0))
                  .padding(5)
                  .textSelection(.enabled)
              }

              Spacer()
            }
            .background(Color(NSColor.textBackgroundColor))
          }
        }
        .padding()
      }

      Spacer()
    }
    .padding()
  }
}
