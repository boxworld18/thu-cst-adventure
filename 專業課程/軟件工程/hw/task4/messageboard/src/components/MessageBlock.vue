<template>
  <el-menu :default-openeds="[]" style="background: #b0c7e7;border-radius: 4px;margin: 5px">
    <el-submenu index="view" style="text-align: left">
      <template slot="title" ><i class="el-icon-chat-square"/>
        <!--请补全这两行注释中间的代码以展示标题-->
				{{title}}
        <!--请补全这两行注释中间的代码以展示标题-->
      </template>
      <div style="display:flex; margin-top: 3px; font-size: small;color: grey">
        <span class="messageblock-datetime" style="padding: 4px;">
          <!--请补全这两行注释中间的代码以展示时间--> 
					{{datetime}}
          <!--请补全这两行注释中间的代码以展示时间-->
        </span>
        <span class="messageblock-user" style="padding: 4px;">{{ user }}</span>
      </div>
      <div class="messageblock-content">{{ message }}</div>
    </el-submenu>
  </el-menu>
</template>

<script>
export default {
	name: "MessageBlock",
	props: {
		title: {
			type:String,
			default: () => "unknown title"
		},
		message: {
			type:String,
			default: () => "unknown content"
		},
		user: {
			type:String,
			default: () => "unknown user"
		},
		timestamp: {
			type:Number,
			default: () => 0
		},
	},
	computed:{
		datetime:function () {
			var d = new Date()
			if (this.timestamp.toString().length == 10) d.setTime(this.timestamp * 1000)
			else d.setTime(this.timestamp)
			return d.toLocaleString()
		}
	}
}
</script>

<style scoped>
    .messageblock-content{
        display: flex;
        color: #090607;
        padding-bottom: 10px;
        font-size: large
    }
</style>