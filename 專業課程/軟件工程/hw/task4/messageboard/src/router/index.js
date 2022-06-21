import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '@/views/Home.vue'
import Stage1 from '@/views/Stage1.vue'
import Stage2 from '@/views/Stage2.vue'
import Stage3 from '@/views/Stage3.vue'

Vue.use(VueRouter)

const routes = [
	{
		path: '/',
		name: 'Home',
		component: Home
	},
	{
		path: '/stage1',
		name: 'Stage1',
		component: Stage1,
	},
	{
		path: '/stage2',
		name: 'Stage2',
		component: Stage2,
	},
	{
		path: '/stage3',
		name: 'Stage3',
		component: Stage3,
	}
]

const router = new VueRouter({
	mode: 'history',
	routes
})

export default router
