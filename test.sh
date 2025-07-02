#!/bin/zsh

meson test -C build --wrap='/usr/bin/time -f "\
🧠 Command:              %C
🧮 Avg Data Size:        %D KB
🕒 Elapsed Time:         %E
🔧 Major Page Faults:    %F
📥 File System Inputs:   %I
📦 Avg Total Memory:     %K KB
🧱 Max Resident Set:     %M KB
📤 File System Outputs:  %O
⚙️ CPU Percentage:       %P
🐾 Minor Page Faults:    %R
🔁 System CPU Time:      %S s
👤 User CPU Time:        %U s
💾 Swaps:                %W
📚 Shared Text Size:     %X KB
📐 System Page Size:     %Z B
⏱️ Invol Context Switch: %c
⌛ Real Time (sec):      %e
🚨 Signals Delivered:    %k
📊 Avg Stack Size:       %p KB
📩 Socket Msgs Received: %r
📤 Socket Msgs Sent:     %s
🗃️ Avg Resident Set:     %t KB
🔄 Vol Context Switch:   %w
✅ Exit Status:          %x"' --verbose
