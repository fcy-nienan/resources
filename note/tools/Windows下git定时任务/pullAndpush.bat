set dir=%1%
set commitMsg=%2%
cd /d %dir%
git checkout wind
git fetch fcy develop:tmp
git merge tmp 
git branch -d tmp

git add .
git commit -m '%commitMsg%'
git push fcy wind:develop
