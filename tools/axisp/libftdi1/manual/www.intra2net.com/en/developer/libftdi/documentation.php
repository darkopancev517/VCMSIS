<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Intra2net &raquo; libFTDI - Documentation</title>
<link rel="stylesheet" type="text/css" media="screen" href="../../screen.css">
<link rel="stylesheet" type="text/css" media="print" href="../../print.css">
</head>

<body>

<!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../de/index.html">
		<div id="logo_screen"><img src="../../../de/pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../de/pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<nav id="navigation">

<a href="documentation.php#navigation"><div class="mobilemenu"><img src="../../../de/pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="documentation.php#"><div class="mobilemenu"><img src="../../../de/pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Products"><a href="../../products/index.html">Products</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../products/index.html">Continue in German</a></li>
		</ul>
	</div>
</li>

<li id="Support"><a href="../../support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../support/antispam/index.html">Blacklist Performance</a></li>
		</ul>
	</div>
</li>

<li id="Developer" class="selected"><a href="../index.html">Developer</a>
	<div class="dropdown">
		<ul>
			<li><a href="index.php">libFTDI</a></li>
			<li><a href="../ipt_ACCOUNT/index.php">ipt_ACCOUNT</a></li>
			<li><a href="../libt2n/index.php">libt2n</a></li>
			<li><a href="../intranator/index.php">Intranator</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">

<div class="subcontainer">
	<ul class="sublist">
<li><a href="index.php">libFTDI</a></li>
<li><a href="download.php">Download</a></li>
<li><a href="repository.php">Repository</a></li>
<li><a href="documentation.php" class="selected">Documentation</a></li>
<li><a href="mailinglist.php">Mailinglist</a></li>
<li><a href="links.php">Links</a></li>
	</ul>
</div>


<div id="content">

<!-- header end -->

<h1>Documentation</h1>

<p>Example code is included in the distribution file.<br>
Here you can find the <a href="documentation/index.html">API documentation</a>.</p>

<p><b>Note:</b> When you get a -5 error &quot;can't claim usb device&quot; during ftdi_usb_open(), make sure the kernel ftdi_sio driver is unloaded.</p>
<p>You also find a patch for <a href="http://savannah.nongnu.org/projects/uisp/">uisp</a> here, an Atmel microcontroller flashing software, to program these via bitbang mode. The patch is not released yet and is only here as a <b>bitbang mode example</b>. Take a look at line 315+ of the patch for code using the bitbang mode.</p>

<!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../imprint.php">Imprint</a>
		<a href="../../contact/index.html">Contact</a>
	</div>
</div>


<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

</body>
</html>
