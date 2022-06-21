const CookieOperation={
    getCookie:(key,defaultValue)=>{
        var rgx = new RegExp("(?:^|(?:; ))"+key+"=([^;]*)")
        var result = document.cookie.match(rgx)
        console.log(result)
        if(result){
            return unescape(result[1])
        }else{
            return defaultValue
        }
    },
    setCookie:(key,value,expire_ms)=>{
        var exdate = new Date();
        exdate.setTime(exdate.getTime() + expire_ms);
        document.cookie = key + "=" + escape(value) + ";expires=" + exdate.toGMTString()
    }
}

export default CookieOperation