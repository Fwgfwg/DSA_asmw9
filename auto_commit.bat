:loop
git add .

git diff --cached --quiet
if %errorlevel%==1 (
    git commit -m "update %date% %time%"
    git push
)

timeout /t 60
goto loop