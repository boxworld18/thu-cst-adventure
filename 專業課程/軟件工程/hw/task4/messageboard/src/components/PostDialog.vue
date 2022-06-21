<template>
  <el-dialog
        style="text-align: center"
        title="发表"
        :visible.sync="dialogVisible"
        :show-close=false   
        :before-close="unVisible"
        width="80%">
    <el-form label-width="80px">
      <el-form-item label="标题">
        <!--请修改这两行注释中间的代码来输入消息标题-->
        <el-input v-model="title" placeholder="title"></el-input>
        <!--请修改这两行注释中间的代码来输入消息标题-->
      </el-form-item>
      <el-form-item label="内容">
        <!--请修改这两行注释中间的代码来输入消息内容-->
        <el-input v-model="message" type="textarea" placeholder="message"></el-input>
        <!--请修改这两行注释中间的代码来输入消息内容-->
      </el-form-item>
      <el-form-item label="发帖名">
        <el-input :disabled="true" v-if="state.username_valid" :value="state.username"/>
        <span v-if="state.username_valid===false" style="color: red">请在主页右上设置名字!</span>
      </el-form-item>
    </el-form>
    <span slot="footer" class="dialog-footer">
      <!--请修改这两行注释中间的代码来产生相应按钮的点击事件-->
      <el-button @click="unVisible">取 消</el-button>
      <el-button type="primary"
                  :disabled="state.username_valid===false"
                  v-on:click="onConfirmClick"
                  >确 定</el-button>
      <!--请修改这两行注释中间的代码来产生相应按钮的点击事件-->
    </span>
  </el-dialog>
</template>

<script>
// 请在下方设计实现自己的数据结构以及函数
export default {
	name: "PostDialog",
	props: {
		dialogVisible: {
			type: Boolean,
			default: () => true
		},
		state: {
			type: Object,
			default: () => {
				return {
					username: "",
					username_valid: false
				}
			}
		},
    push: {
      type: Function,
      default: () => {
        return () => {}
      }
    },
    unVisible: {
      type: Function,
      default: () => {
        return () => {}
      }
    }
	},
	data(){
		return {
      title: "",
      message: "",
		}
	},
	methods: {
    onConfirmClick() {
      this.push(this.title, this.message)
    } 
	}
}
</script>