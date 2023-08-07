#!/bin/bash
while true; do
    echo "Enter your commit message (or type 'exit' to stop auto-pushing): "
    read commit_message
    if [ "$commit_message" = "exit" ]; then
        echo "Exiting the auto-push script."
        break
    fi

    git add .
    git commit -m "$commit_message"
    git push

    echo "Auto-push completed..."
done
