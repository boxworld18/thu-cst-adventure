/**
 * 如果需要修改为正常上线模式，请注释下面mock的import代码
 * **/
// import "@/mock/index"

// 请在下方实现自己的后端通信函数

import axios from 'axios'

const Communication={
  sendMessage: async (title, message) => {
    try {
      const response = await axios
        .post('/api/message', {
          title: title,
          content: message,
        })
      var data = new Object();
      data = response.data.code
      return data
    }
    catch (e) {
      console.error(e)
      return 400
    }
  },
  getMessage: async () => {
    try {
      const response = await axios.get("/api/message")
      var data = new Object()
      data = response.data.data
      return data
    } 
    catch (e) {
      console.error(e)
      return []
    }
  }
}

export default Communication