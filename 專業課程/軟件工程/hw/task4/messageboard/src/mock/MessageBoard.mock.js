//var Mock = require('mockjs')
import * as  Mock from "better-mock"
import API from "@/utils/API"

Mock.setup({timeout:"200-400"})

var messageList = Array(5).fill(
	{
		"user": "Alice",
		"title":"[英超]切尔西2-1胜10人曼城 利物浦提前7轮夺冠",
		"content":"北京时间6月26日03:15(英国当地时间25日20:15)，2019/20赛季英超第31轮一场焦点战在斯坦福桥球场展开争夺，切尔西主场2比1力克曼城，普利西奇和威廉进球，费尔南迪尼奥送出红点。切尔西3连胜，曼城客场连败送利物浦提前7轮夺冠。",
		"timestamp":1593133200}
)
Mock.mock(API.GET_MESSAGE_LIST.path,API.GET_MESSAGE_LIST.method,(rqst)=>{
	console.log(rqst)
	return {
    "code": 200,
    "data": messageList
  }
})
Mock.mock(API.POST_NEW_MESSAGE.path,API.POST_NEW_MESSAGE.method,(rqst)=>{
	console.log(rqst)
	messageList.push({
		"user":unescape(rqst.headers.Cookie.match(new RegExp("user=([^;]*)"))[1]),
		"title":rqst.body.title,
		"content":rqst.body.content,
		"timestamp":Math.round(new Date().getTime() / 1000),
	})
	return {
    "code": 201,
    "data": "message was sent successfully"
  }
})