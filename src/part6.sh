
STAGE_TYPE=$1
BOT_TOKEN="7202987834:AAFi2_OWtXUf3Im8PiRJbCRHrG9GTgET9Gs"
CHAT_ID="562312911"

sleep 3

if [ "$CI_JOB_STATUS" == "success" ]; then
  MESSAGE="✅ Стадия $STAGE_TYPE $CI_JOB_NAME успешно завершена  $CI_PROJECT_URL/pipelines"
else
  MESSAGE="🚫 Стадия $STAGE_TYPE $CI_JOB_NAME завершилась с ошибкой!  $CI_PROJECT_URL/pipelines"
fi

curl -X POST "https://api.telegram.org/bot$BOT_TOKEN/sendMessage" -d chat_id=$CHAT_ID -d text="$MESSAGE"