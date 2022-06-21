<template>
  <div id="message-list">
    <!--请修改这两行注释中间的代码，达到用多个MessageBlock来展示messageList数据的效果-->
			
			<MessageBlock v-for="(message, index) in messageList" :key="index"
			:title="message.title" :message="message.content" :user="message.user" :timestamp="message.timestamp"/>

    <!--请修改这两行注释中间的代码，达到用多个MessageBlock来展示messageList数据的效果-->
  </div>
</template>

<script>
import MessageBlock from "@/components/MessageBlock"

export default {
	name: "MessageList",
	components: {
		MessageBlock
	},
	props: {
		messageList: {
			type: Array,
			default: () => new Array(5).fill({
				title: "Hello",
				message: "Hello World!",
				user: "unknown",
				timestamp: new Date().getTime()
			})
		}
	}
}
</script>
