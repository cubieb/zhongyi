/**
 * Created by hp on 2017/5/17.
 */
$(function () {
    $(".refresh-btn").on("click", function () {
        $.ajax({
            url: "",
            type: "POST",
            success: function (data) {
                console.log(data);
            }
        });
    });

    var listBtn = $("#wifi-list>.wifi-name>.wifi-r>.list-btn");
    listBtn.on("click", function (e) {
        $.ajax({
            url:"/cgi-bin/test.cgi",
            type:"POST",
            success:function (data) {
                //alert(data);
		var response = JSON.parse(data);
                console.log(response);
		console.log(typeof response);
                var html = template("listTmp", response);
		console.log(html);
                $('#selectCon').html(html);
            }
        });

        e.stopPropagation();//不出现事件的原因是浏览器还有默认事件。
        $(".selectContainer").select();
    });
});
