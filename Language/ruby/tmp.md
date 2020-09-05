params = ActionController::Parameters.new(json)

.permit(:document=>{},:attachments=>[],:icons=>[],:label_ids=>[],:instructor_teacher_ids=>[],:access_token=>"",:user_session_key=>"",:controller=>"",:action=>"",:format=>"",:user=>{},:organization=>{})

client = Atyun::AliCloud::Oss.client
OSS = Aliyun::OSS

buckets = client.list_buckets
buckets.each { |b| puts b.name }
bucket = client.get_bucket('mozhou-prod')
bucket = client.get_bucket('mozhou-prod-public')
bucket = client.get_bucket('mozhou-prod2-public')
bucket = client.get_bucket('mozhou-videos-20200902')
bucket = client.get_bucket('mozhou-prod2-public')


dir = "墨舟手动同步文件目录/校区资源整理/单字视频/"
dir = "mozhou-app-prod/"
dir = "" 

objects = bucket.list_objects(:prefix =>dir,:delimiter=>'/')
  objects.each do |obj|
    next if !obj.is_a?(OSS::Object)       
    puts "SubDir: #{obj.to_json}"
  end

client = Atyun::AliCloud::Oss.client
OSS = Aliyun::OSS











https://mozhou-prod.oss-cn-shanghai.aliyuncs.com/%E5%A2%A8%E8%88%9F%E6%89%8B%E5%8A%A8%E5%90%8C%E6%AD%A5%E6%96%87%E4%BB%B6%E7%9B%AE%E5%BD%95/%E6%A0%A1%E5%8C%BA%E8%B5%84%E6%BA%90%E6%95%B4%E7%90%86/class_picture/030410.jpg



bucket = client.get_bucket('my-bucket')
# 生成URL，默认带签名，有效时间为60秒
puts bucket.object_url('my-object')
# http://my-bucket.oss-cn-hangzhou.aliyuncs.com/my-object?Expires=1448349966&OSSAccessKeyId=5vxxxx&Signature=aM2HpBLeMq1aec6JCd7BBAKYiwI%3D

# 不带签名的URL
puts bucket.object_url('my-object', false)
# http://my-bucket.oss-cn-hangzhou.aliyuncs.com/my-object

# 指定URL过期时间为1小时（3600秒）
puts bucket.object_url('my-object', true, 3600)





path = "/Users/nienan/Downloads/"
fd = getFileAndDeal[1]
xls = Roo::Spreadsheet.open(path + fd[:fileName])
sheet = xls.sheet(0)
items = sheet.first_row.present? ? sheet.to_a : []
items.delete_at(0);
item = items[0]
json = get_image_json item