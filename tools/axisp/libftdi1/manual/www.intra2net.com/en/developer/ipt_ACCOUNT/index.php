<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Intra2net &raquo; ipt_ACCOUNT</title>
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

<a href="index.php#navigation"><div class="mobilemenu"><img src="../../../de/pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="index.php#"><div class="mobilemenu"><img src="../../../de/pictures/mobile_icon.gif" alt="Navigation"></div></a>

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
			<li><a href="index.php">ipt_ACCOUNT</a></li>
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
<li><a href="index.php" class="selected">ipt_ACCOUNT</a></li>
<li><a href="download.php">Download</a></li>
<li><a href="repository.php">Repository</a></li>
<li><a href="documentation.php">Documentation</a></li>
<li><a href="mailinglist.php">Mailinglist</a></li>
<li><a href="links.php">Links</a></li>
	</ul>
</div>


<div id="content">

<!-- header end -->

<h1>ipt_ACCOUNT</h1>

<p>ipt_ACCOUNT is a high performance <b>local network accounting
system</b> written for the Linux netfilter/iptables system.<br>
<br>
</p>


<h2>News</h2>

<b>2011-01-19:</b> Version 1.16 of ipt_ACCOUNT released
<ul>
<li>Support for kernel 2.6.36 / 2.6.37</li>
<li>Support for iptables 1.4.3 and 1.4.4 by Blazej<br>
iptables 1.4.2 and below is no longer supported</li>

</ul>

<b>2009-04-14:</b> Version 1.15 of ipt_ACCOUNT released
<ul>
<li>Support for kernel 2.6.29 / 2.6.28 and newer</li>
</ul>

<strong>2009-02-05:</strong> Developer section improvements
<ul>
<li>Public repositories for simple contribution</li>
<li>Mailinglists for better user communication</li>
<li>Clear structure and therefore new URLs (update Links please)</li>
</ul>


<h2> Description </h2>

<p> ipt_ACCOUNT is designed to be queried for data every second or at
least every ten seconds. It is written as kernel module to handle
high bandwidths without packet loss. </p>
<p>The largest possible subnet size is 24 bit, meaning f.e.
10.0.0.0/8 networks. Therefore it's able to use a fixed internal
data structures which speeds up the processing speed for each
packet. Furthermore, accounting data for one complete 192.168.1.X/24
network takes 4kb of memory. Memory for 16 or 24 bit networks is
only  allocated when needed.</p>
<p>The data is queried using the userspace libipt_ACCOUNT library.
There is no /proc interface as it would be too slow for continuous
access. The read&amp;flush query operation is the fastest, as no
internal data snapshot needs to be created&amp;copied for all data.
Use the &quot;read&quot; operation without flush only for debugging
purposes!</p>
<p>To optimize the kernel&lt;-&gt;userspace data transfer a bit
more, the kernel module only transfers information about IPs, where
the src/dst packet counter is not 0. This saves precious kernel
time.</p>


<h2>License</h2>

<p>ipt_ACCCOUNT is licensed  under <a href="http://www.gnu.org/licenses/old-licenses/gpl-2.0.html">GPL 2</a> (not any later)</p>


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
