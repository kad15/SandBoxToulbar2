#!/bin/bash
git pull origin master 1>/dev/null 2>&1
git add . 1>/dev/null 2>&1
git commit -m "rapport PFE" 1>/dev/null 2>&1
git push origin master 1>/dev/null 2>&1
git push origin master 1>/dev/null 2>&1
git push origin master | grep "Everything up-to-date"
echo "Rapport publié sur GitHub"
sleep 2s
