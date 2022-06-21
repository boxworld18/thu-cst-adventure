import re
from django.shortcuts import render
from django.http import JsonResponse, HttpResponse
import json

from matplotlib.pyplot import title
from .models import User, Message
from django.core.exceptions import ValidationError
from django.core.files import File

# Create your views here.
def message(request):
    def gen_response(code: int, data: str):
        return JsonResponse({
            'code': code,
            'data': data
        }, status=code)

    if request.method == 'GET':
        limit = request.GET.get('limit', default='100')
        offset = request.GET.get('offset', default='0')
        if not limit.isdigit():
            return gen_response(400, '{} is not a number'.format(limit))
        if not offset.isdigit():
            return gen_response(400, '{} is not a number'.format(offset))

        return gen_response(200, [
                {
                    'title': msg.title,
                    'content': msg.content,
                    'user': msg.user.name,
                    'timestamp': int(msg.pub_date.timestamp())
                }
                for msg in Message.objects.all().order_by('-pub_date')[int(offset) : int(offset) + int(limit)]
            ])

    elif request.method == 'POST':
        # 从cookie中获得user的名字，如果user不存在则新建一 个
        # 如果cookie中没有user则使用"Unknown"作为默认用户名
        name = request.COOKIES['user'] if 'user' in request.COOKIES else 'Unknown'
        user = User.objects.filter(name=name).first()
        if not user:
            user = User(name = name)
            try:
                user.full_clean()
                user.save()
            except ValidationError as e:
                return gen_response(400, "Validation Error of user: {}".format(e))

        # 验证请求的数据格式是否符合json规范，如果不符合则返回code 400
        # -------------------------------------------------------------------------------
        try:
            body = json.loads(request.body)
        except ValueError as e:
            return gen_response(400, "Json Value Error")
        
        # 验证请求数据是否满足接口要求，若通过所有的验证，则将新的消息添加到数据库中
        # PS: {"title": "something", "content": "someting"} title和content均有最大长度限制
        # -------------------------------------------------------------------------------

        if 'title' not in body or 'content' not in body:
            return gen_response(400, "Json Value Error")

        title = body['title']
        content = body['content']

        try:
            message = Message.objects.create(user = user, title = title, content = content)
            message.full_clean()
            message.save()
        except ValidationError as e:
            return gen_response(400, "Validation Error: {}".format(e))

        # 添加成功返回code 201
        return gen_response(201, "message was sent successfully")

    else:
        return gen_response(405, 'method {} not allowd'.format(request.method))


# 一键清空留言板接口 TODO
def clearmessage(request):
    def gen_response(code: int, data: str):
        return JsonResponse({
            'code': code,
            'data': data
        }, status=code)

    Message.objects.all().delete()

    return gen_response(200, "message was cleared successfully")

# 返回某个用户的所有留言 TODO
def messages_for_user(request):
    def gen_response(code: int, data:str):
        return JsonResponse({
            'code': code,
            'data': data
        }, status=code)

    try:
        body = json.loads(request.body)
    except ValueError as e:
        return gen_response(400, [])

    if 'user' not in body:
        return gen_response(400, [])
    
    name = body['user']
    user = User.objects.filter(name=name).first()

    if not user:
        return gen_response(400, [])

    result = Message.objects.filter(user=user).all().order_by('-pub_date').values()
    data = list(entry for entry in result)

    return gen_response(200, data)

# AVATAR 用户头像 TODO
def avatar(request):

    def gen_response(code: int, data:str):
        return JsonResponse({
            'code': code,
            'data': data
        }, status=code)

    if request.method == 'GET':

        if 'user' in request.GET:
            # 找到头像
            # return HttpResponse(???, content_type='image/png')

            name = request.GET.get('user')
            user = User.objects.filter(name=name).first()

            if not user:
                return gen_response(200, "User not found")

            pic = user.avatar

            return HttpResponse(pic, content_type='image/png')
            
        else:
            return gen_response(200, "invaild operation")

    elif request.method == 'POST':
        # 提示：
        #   user = request.POST['user'] 
        #   pic = request.FILES['pic']

        if 'user' not in request.POST:
            return gen_response(400, "Json Value Error")

        if 'pic' not in request.FILES:
            return gen_response(400, "Json Value Error")

        name = request.POST['user']
        pic = request.FILES['pic']

        user = User.objects.filter(name=name).first()
        if not user:
            user = User(name = name)
        
        if not pic:
            return gen_response(400, "No image uploaded")

        user.avatar = pic

        try:
            user.full_clean()
            user.save()
        except ValidationError as e:
            return gen_response(400, "Validation Error")

        return gen_response(200, "upload successfully")

    else:
        return HttpResponse('method {} not allowd'.format(request.method), status=405)
