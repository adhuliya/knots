wget -- and its use cases
====================

Important Files
----------------------
* The [`man wget`](man_wget.txt) page is very useful.

FAQs
---------------------
### How to send get request?

    wget -S --header="Accept-Encoding: gzip, deflate" \
         -O response.txt http://server:8080/application/params

### How to send post request?

    wget -S --header="Accept-Encoding: gzip, deflate" \
        --header='Accept-Charset: UTF-8' --header='Content-Type: application/json' \
        -O response.json \
        --post-data '{"param1":"myspecialValue1","param2":"my special value 2"}' \
        http://server:8080/application2/params2

### How to handle cookies and login?
From `man wget`:
    
    ...
    This example shows how to log in to a server using POST and then proceed to download the
    desired pages, presumably only accessible to authorized users:
    
            # Log in to the server.  This can be done only once.
            wget --save-cookies cookies.txt \
                 --post-data 'user=foo&password=bar' \
                 http://example.com/auth.php
    
            # Now grab the page or pages we care about.
            wget --load-cookies cookies.txt \
                 -p http://example.com/interesting/article.php

    ...
    
   
<div class="footer">
<br/>
&copy; Anshuman Dhuliya
<br/>
</div>

