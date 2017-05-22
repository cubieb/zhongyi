/**
 * Created by hp on 2017/5/17.
 */
(function ($) {
    jQuery.fn.select = function (options) {
        return this.each(function () {
            var $this = $(this);
            var $shows = $this.find(".shows");
            var $selectOption = $this.find(".selectOption");
            var $el = $this.find("ul > li");
            console.log("111");


            $this.toggleClass("zIndex");
            $this.children("ul").toggleClass("dis");//显示隐藏
            

            $el.bind("click", function () {
                var $this_ = $(this);
                $("#wifi-list>.wifi-name>.wifi-l").text($this_.text());
            });

            $("body").bind("click", function () {
                $this.removeClass("zIndex");
                $this.find("ul").removeClass("dis");
            })

            //eahc End
        });

    }

})(jQuery);