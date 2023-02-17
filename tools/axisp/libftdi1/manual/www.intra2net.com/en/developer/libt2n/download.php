<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Intra2net &raquo; libt2n - Download</title>
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

<a href="download.php#navigation"><div class="mobilemenu"><img src="../../../de/pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="download.php#"><div class="mobilemenu"><img src="../../../de/pictures/mobile_icon.gif" alt="Navigation"></div></a>

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
			<li><a href="../libftdi/index.php">libFTDI</a></li>
			<li><a href="../ipt_ACCOUNT/index.php">ipt_ACCOUNT</a></li>
			<li><a href="index.php">libt2n</a></li>
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
<li><a href="index.php">libt2n</a></li>
<li><a href="download.php" class="selected">Download</a></li>
<li><a href="repository.php">Repository</a></li>
<li><a href="documentation.php">Documentation</a></li>
<li><a href="mailinglist.php">Mailinglist</a></li>
<li><a href="links.php">Links</a></li>
	</ul>
</div>


<div id="content">

<!-- header end -->

<h1>Download</h1>

<table width="100%" border="0" cellspacing="0" cellpadding="4">
<tr>
<td><b>Changelog</b></td>
<td><a href="http://developer.intra2net.com/git/?p=libt2n;a=blob;f=ChangeLog;hb=refs/tags/latest_release">Short</a> &nbsp; <a href="http://developer.intra2net.com/git/?p=libt2n;a=shortlog;h=refs/tags/latest_release">All commits</a></td>
<td>&nbsp;</td>
</tr>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>

<tr>
<td width="23%"><b>Source TGZs</b></td>
<td width="45%"><a href="download/libt2n-0.6.tar.gz">libt2n-0.6.tar.gz</a></td>
<td width="32%"><a href="download/libt2n-0.6.tar.gz.sig">Signature</a></td>
</tr>

<tr>
<td>&nbsp;</td>
<td><a href="download/libt2n-0.5.tar.gz">libt2n-0.5.tar.gz</a></td>
<td><a href="download/libt2n-0.5.tar.gz.sig">Signature</a></td>
</tr>

<tr>
<td>&nbsp;</td>
<td><a href="download/libt2n-0.4.tar.gz">libt2n-0.4.tar.gz</a></td>
<td><a href="download/libt2n-0.4.tar.gz.sig">Signature</a></td>
</tr>

</table>
<br>
<br>
<br>

<h2>Requirements and dependencies</h2>

<p>Using the library:</p>
<ul>
<li><a href="http://www.boost.org/libs/serialization/doc/">Boost serialization</a></li>
</ul>
<p><br>
Building new servers:
<ul>
<li><a href="http://www.gccxml.org">gccxml</a></li>
<li><a href="http://libxmlplusplus.sourceforge.net/">libxmlpp</a></li>
<li><a href="http://pkgconfig.freedesktop.org/wiki/">pkg-config</a> (strongly recommended)</li>
<li>GNU autotools (autoconf, automake, libtool)<br>
</li>
</ul>

<p>&nbsp;</p>

<h2>Signature and Fingerprint </h2>

<p>All releases are signed with <a href="../opensource.intra2net.com.asc">our GPG-key (ID 24F006F5)</a>.<br>
The fingerprint is
<pre>3CEA 9B88 68BC 3852 618E B5B4 707F 91A4 24F0 06F5</pre></p>


<h3>How to verify </h3>

<ol>
<li><a href="../opensource.intra2net.com.asc"><b>Download</b> our GPG-Key:</a><br>
and the source you want to check with signature-file<br>
<br>
<br>
</li>
    <li><b>Import</b> our GPG-Key:
<pre>gpg --import opensource.intra2net.com.asc<br><br></pre></li>
    <li><b>Sign</b> our GPG-Key (non-exportable):
<pre>gpg --lsign-key 24F006F5<br><br></pre></li>
    <li><b>Verify</b> the signature like this:
<pre>gpg --verify libt2n-0.5.tar.gz.sig<br><br></pre></li>
</ol>


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
