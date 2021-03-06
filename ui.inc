<?php
/*
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


require_once("utils.inc");


function genTitle($addl = "") {
	global $gbMobile, $gbAndroid, $gbChrome, $gbIe, $gbIphone;

	return "HTTP Archive " . 
		( $gbMobile ? "Mobile " : "" ) . 
		( $gbAndroid ? "Android " : "" ) . 
		( $gbChrome ? "Chrome " : "" ) . 
		( $gbIphone ? "iPhone " : "" ) . 
		( $gbIe ? "IE " : "" ) . 
		( $addl ? " - $addl" : "" );
}


function globalCss() {
	return <<<OUTPUT
<style>
BODY { font-family: Arial; }
.header { border-bottom: 4px groove #17598F; font-size: 3em; color: #17598F; }
.preheader { font-size: 0.8em; }
.notification { color: #C00; }
.tdnum { text-align: right; }
</style>

OUTPUT;
}


// HTML to insert first inside the HEAD element.
function headfirst() {
	$sHtml = "";

	// Google Analytics
	if ( ! isPrivateInstance() ) {
		$sHtml = <<<OUTPUT
<script type="text/javascript">
// Google Analytics
var _gaq = _gaq || [];
_gaq.push(['_setAccount', 'UA-22381566-1']);
_gaq.push(['_setDomainName', '.httparchive.org']);
_gaq.push(['_trackPageview']);
_gaq.push(['_trackPageLoadTime']);
(function() {
	var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
})();
</script>

OUTPUT;
	}

	$sHtml .= <<<OUTPUT
<script type="text/javascript">
function loadScript(url, callback) {
	var sNew = document.createElement("script");
	sNew.async = true;
	sNew.src = url;
	if ( "function" === typeof(callback) ) {
		sNew.onload = function() {
			callback();
			sNew.onload = sNew.onreadystatechange = undefined; // clear it out to avoid getting called twice
		};
		sNew.onreadystatechange = function() {
			if ( "loaded" === sNew.readyState || "complete" === sNew.readyState ) {
				sNew.onload();
			}
		}
	}
	var s0 = document.getElementsByTagName('script')[0];
	s0.parentNode.insertBefore(sNew, s0);
}

var _jqueryq = [];
function doJquery() {
	for ( var i=0; i < _jqueryq.length; i++ ) {
		var cmd = _jqueryq[i];
		doCommand(cmd);
	}
	_jqueryq = undefined; // as a flat that future commands should be done immediately
}

function addCommand(cmd) {
	if ( "undefined" === typeof(_jqueryq) ) {
		doCommand(cmd);
	}
	else {
		_jqueryq.push(cmd);
	}
}

function doCommand(cmd) {
	if ( "function" === typeof(cmd) ) {
		cmd();
	}
	else if ( "string" === typeof(cmd) ) {
		// Eval a string of JavaScript in the proper context.
		if (window.execScript) {
			window.execScript(cmd);
		}
		else {
			var fn = function() {
				window.eval.call(window, cmd);
			};
			fn();
		}
	}
}

loadScript("http://ajax.googleapis.com/ajax/libs/jquery/1.5.1/jquery.min.js");
</script>

<!--[if lt IE 9]>
<script>
// we use some new HTML tags - make them work in IE<9 - hrrmphf
var e = ("abbr,article,aside,audio,canvas,datalist,details,figure,footer,header,hgroup,mark,menu,meter,nav,output,progress,section,time,video").split(',');
for (var i = 0; i < e.length; i++) {
	document.createElement(e[i]);
}
</script>
<![endif]-->

OUTPUT;

    return $sHtml;
}


function uiHeader($title = "HTTP Archive", $bNavlinks = true, $extraNav='') {
	global $gbMobile, $gbAndroid, $gbChrome, $gbDev, $gbDesktop, $gbIe, $gbIphone;

	$navlinks = "";
	if ( $bNavlinks ) {
		// Make sure to echo the drop down list of "About" links in about.php.
		$navlinks = '
<nav>
<ul>
  <li> <a id="trendsnav" href="trends.php">Trends</a>
  <li> <a id="statsnav" href="interesting.php">Stats</a>
  <li><a id="websitesnav" href="websites.php">Websites</a>
  <li><a id="discussnav" href="https://discuss.httparchive.org/">Discuss</a>
  <li id="aboutnav" onmouseover="document.getElementById(\'aboutdropdown\').style.display=\'block\';" onmouseout="document.getElementById(\'aboutdropdown\').style.display=\'none\';"><a href="about.php">About</a>
    <ul id="aboutdropdown">
 	  <li><a href="about.php#mission">Mission</a></li>
	  <li><a href="about.php#faq">FAQ</a></li>
 	  <li><a href="downloads.php">Download Data</a></li>
 	  <li><a href="urls.php">URLs</a></li>
 	  <li><a href="https://github.com/HTTPArchive/httparchive">Source Code</a></li>
 	  <li><a href="https://github.com/HTTPArchive/httparchive/issues">Bugs</a></li>
 	  <li><a href="https://discuss.httparchive.org/">Contact Us</a></li>
 	</ul>
  </li>
</ul>
</nav>';
	}

	$sSelected = "style='border: 1px solid;'";
	$sublogo = "<div class=sublogo>" .
		"<a href=" . ( $gbDesktop ? "'/' $sSelected" : "'//httparchive.org'" ) . ">DESKTOP</a>" .
		"<a href=" . ( $gbMobile ? "'/' $sSelected" : "'//mobile.httparchive.org'" ) . ">MOBILE</a>";
	if ( $gbChrome ) {
		$sublogo .= "<a href='/' $sSelected>Chrome</a>";
	}
	else if ( $gbAndroid ) {
		$sublogo .= "<a href='/' $sSelected>Android</a>";
	}
	else if ( $gbIe ) {
		$sublogo .= "<a href='/' $sSelected>IE</a>";
	}
	else if ( $gbIphone ) {
		$sublogo .= "<a href='/' $sSelected>iPhone</a>";
	}
	$sublogo .= "</div>";

	return <<<OUTPUT
    <header>
		<a href="index.php" id="logo" style="line-height: 0.7em;">HTTP Archive</a>
		$sublogo
		$navlinks
	</header>

OUTPUT;
}


function uiFooter() {
	return <<<OUTPUT
<footer style="text-align: center; margin-left: 8em; margin-right: 8em;">
<a href="about.php#sponsors">sponsors</a>: 
<a title="Google" href="http://www.google.com/">Google</a>,
<a title="Mozilla" href="http://www.mozilla.org/firefox">Mozilla</a>,
<a title="New Relic" href="http://www.newrelic.com/">New Relic</a>,
<a title="O'Reilly Media" href="http://oreilly.com/">O&#8217;Reilly Media</a>,
<a href="http://www.etsy.com/">Etsy</a>,
<a title="dynaTrace Software" href="http://www.dynatrace.com/">dynaTrace</a>,
<a title="Instart Logic" href="http://instartlogic.com/">Instart Logic</a>,
<a title="Catchpoint Systems" href="http://www.catchpoint.com/">Catchpoint Systems</a>,
<a title="Fastly" href="http://bit.ly/1nWd1oL">Fastly</a>,
<a title="SOASTA mPulse" href="https://www.soasta.com/mpulse/sign-up/">SOASTA mPulse</a>,
and
<a title="Hosting Facts" href="https://hostingfacts.com/">Hosting Facts</a>.
<br>
powered by <a href="http://www.webpagetest.org">WebPagetest</a>
</footer>
OUTPUT;
}

?>
