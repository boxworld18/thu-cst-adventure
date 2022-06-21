<template>
  <el-dialog
      style="text-align: center"
      title="设置发帖名"
      :visible.sync="loginDialog.dialogVisible"
      width="40%">
    <span>这里不做登录校验，仅仅演示一个设置功能</span>
    <el-form :model="loginDialog.form" label-width="80px">
      <span style="color: red" v-if="loginDialog.dialogError!==''">{{loginDialog.dialogError}}</span>
      <el-form-item v-if="state.username_valid" label="原用户名">
        <el-input disabled :value="state.username"/><!-- 仅作提示作用 -->
      </el-form-item>
      <el-form-item label="用户名">
        <el-input v-model="loginDialog.form.username" :aria-placeholder="state"/>
      </el-form-item>
    </el-form>
    <span slot="footer" class="dialog-footer">
    <el-button v-on:click="loginDialog.dialogVisible = false">返回</el-button>
    <el-button type="primary"
      :disabled="((state.username_valid) && (state.username===loginDialog.form.username))"
      v-on:click="setUserName">
    <span v-if="state.username_valid">修改</span>
    <span v-else>设置</span>
    </el-button>
  </span>
  </el-dialog>
</template>

<script>
// 请在下方设计实现自己的数据结构以及函数(可以自行添加回调函数在props里)
import CookieOperation from "@/utils/tools.js"
export default {
  name: "LoginDialog",
  props: {
    loginDialog: {
      type: Object,
      default: () => {
        return {
          dialogVisible:false,
          dialogError:"",
          form:{
            username:""
          }
        }
      }
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
    updateUsername: { //外部传入传递回调函数， 父组件的变量只能由父组件自己修改，子组件不能修改父组件传入的props
      type:Function,
      default: ()=>{
        return ()=>{}
      }
    }
  },
  methods:{
    setUserName() {
      //补全此处代码时可以使用utils/tools.js中的代码
      CookieOperation.setCookie("user", this.loginDialog.form.username, 1e9);
      this.loginDialog.dialogVisible = false;
      this.updateUsername(this.loginDialog.form.username);
    },
  }
}
</script>

<style scoped>

</style>