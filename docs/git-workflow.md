# Git Configuration and Repository Workflow

Git identity is configured locally on the computer and should not be committed as a project file.

## One-time Git identity setup

Replace the placeholders with the account details you intend to use:

```bash
git config --global user.name "Your Name"
git config --global user.email "your-verified-github-email@example.com"
```

Check the configuration:

```bash
git config --global --list
```

## Clone the repository

```bash
git clone https://github.com/sdivyadarshan/Ultrasonic-Radar-System-using-uno-and-HTML-linking.git
cd Ultrasonic-Radar-System-using-uno-and-HTML-linking
```

## Commit and push local changes

```bash
git status
git add README.md src web hardware docs media .gitignore
git commit -m "Add Arduino ultrasonic radar project package"
git push origin main
```

Do not add personal access tokens, passwords, private keys, or local machine-specific Git configuration to the repository.

## License

The repository already contains an MIT License. Keep the existing license file unless the copyright owner deliberately chooses to change it.
