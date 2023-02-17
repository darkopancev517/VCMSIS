<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Intra2net &raquo; ipt_ACCOUNT - Documentation</title>
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
<li><a href="index.php">ipt_ACCOUNT</a></li>
<li><a href="download.php">Download</a></li>
<li><a href="repository.php">Repository</a></li>
<li><a href="documentation.php" class="selected">Documentation</a></li>
<li><a href="mailinglist.php">Mailinglist</a></li>
<li><a href="links.php">Links</a></li>
	</ul>
</div>


<div id="content">

<!-- header end -->

<h1>Installation</h1>

<p>- Install the pom-ng-ipt_ACCOUNT archive in your patch-o-matic-ng directory<br>
- Patch your kernel and userspace iptables tool: &quot;./runme ACCOUNT&quot;<br>
- Recompile the kernel and iptables<br>
<p>- Unpack the libipt_ACCOUNT library archive<br>
- Run autoreconf -f<br>
- ./configure &amp;&amp; make &amp;&amp; make install</p>
<p>You can also install &amp; build the provided .src.prm</p>


<h1>Usage</h1>

<p> It takes two parameters:<br>
--addr is the subnet which is accounted for<br>
--tname is the table name where the information is stored</p>
<p>The data can be queried later using the libipt_ACCOUNT userspace
library or by the &quot;iptaccount&quot; tool which is part of the
libipt_ACCOUNT package.</p>
<p>A special subnet is &quot;0.0.0.0/0&quot;: All data is stored in
the src_bytes and src_packets structure of slot &quot;0&quot;. This
is useful if you want to account the overall traffic to/from your
internet provider.</p>
<p>Here's an example:<br>
iptables -A OUTPUT -j ACCOUNT --addr 0.0.0.0/0 --tname all_outgoing<br>
iptables -A OUTPUT -j ACCOUNT --addr 192.168.1.0/24 --tname sales</p>
<p>This creates two tables called &quot;all_outgoing&quot; and
&quot;sales&quot; which can be queried using the userspace
library/iptaccount tool.<br>
</p>
<p><b>What can I do with the userspace &quot;iptaccount&quot; tool?</b><br>
&quot;iptcount&quot; is a reference implementation to show the usage<br>
of the libipt_ACCOUNT library. It features the following commandline options:</p>
<p>[-u] show kernel handle usage<br>
[-h] free all kernel handles (experts only!)<br>
[-a] list all table names</p>
<p>[-l name] show table data<br>
[-f] flush data after show<br>
[-c] loop every second (abort with CTRL+C)</p>
<p>Here's the output of an iptaccount session:</p>
<p>ipt_ACCOUNT userspace accounting tool v1.0</p>
<p>Showing table: outgoing<br>
Run #0 - 1 item found<br>
IP: 0.0.0.0 SRC packets: 4 bytes: 1128 DST packets: 0 bytes: 0<br>
Finished.</p>


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
