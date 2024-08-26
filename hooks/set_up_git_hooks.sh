#!/bin/bash

echo "Installing Git hooks..."

# Create .git/hooks if it does not exist
mkdir -p ../.git/hooks

# Copy hooks from hooks/ to .git/hooks
cp hooks/* ../.git/hooks/

# Make hooks executable
chmod +x ../.git/hooks/*

echo "Git hooks installed."
