<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Intra2net &raquo; libt2n</title>
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
<li><a href="index.php" class="selected">libt2n</a></li>
<li><a href="download.php">Download</a></li>
<li><a href="repository.php">Repository</a></li>
<li><a href="documentation.php">Documentation</a></li>
<li><a href="mailinglist.php">Mailinglist</a></li>
<li><a href="links.php">Links</a></li>
	</ul>
</div>


<div id="content">

<!-- header end -->

<h1>libt2n - C++ library for IPC</h1>

<p>libt2n (talk to neighbor) is a C++ <b>library for inter-process communication</b> (IPC) with an additional code generator (libt2n-codegen)</p>


<h2>News</h2>

<p>
<strong>2011-05-20:</strong> Version 0.6 of libt2n released
<ul>
<li>Switch license to GPLv2 + linking exception</li>
<li>Don't rethrow unknown exceptions</li>
<li>Migrate to Boost unit test framework</li>
<li>gccxml wrapper: Filter -pthread from newer gcc versions</li>
<li>rpm package: Build in parallel</li>
</ul>

<strong>2009-02-07:</strong> Version 0.5 of libt2n released
<ul>
<li>New project home</li>
<li>Fixed calls to virtual functions in constructors/destructors</li>
<li>Improvements for data transfers larger than 2 GB</li>
<li>Fixed uninitialized variables causing random transfer problems</li>
</ul>

<strong>2009-02-05:</strong> Developer section improvements
<ul>
<li>Public repositories for simple contribution</li>
<li>Mailinglists for better user communication</li>
<li>Clear structure and therefore new URLs (update Links please)</li>
</ul>

</p>


<h2>Description</h2>

<p>Before inventing our own IPC library, we checked a lot of other IPC frameworks like <a href="http://www.omg.org/gettingstarted/corbafaq.htm">CORBA</a>, <a href="http://www.freedesktop.org/wiki/Software/dbus">D-BUS</a> and <a href="http://www.zeroc.com/">ICE</a>. But they weren't easy
to use (you need many lines of code to export or use a method, let alone good error handling) and did not allow passing complex
C++ objects like vectors, maps and your own classes. To get all this we had to develop our own framework.<br><br>
Here's a list of goals we had in mind while developing:</p>

<ul>
    <li>easy to use, mimimum of code-lines needed to export and use methods</li>
    <li>handles complex C++ structures like maps of vectors, etc.</li>
    <li>passes exceptions from the server back to the caller</li>
    <li>easy integration into autotools and pkg-config</li>
</ul>

<p>Of course we had to limit the feature set, so libt2n currently has these restrictions:</p>

<ul>
    <li>C++ only</li>
    <li>Synchronous, blocking, no callbacks</li>
    <li>no server-side objects, just functions you can call</li>
    <li>no threads or multiple server processes for handling multiple requests at once</li>
</ul>

<p>Communication between client and server is currently done using Unix domain sockets (named pipes) or TCP. But the library is designed
transport-independent, so it can be expanded to shared memory or other mechanisms.</p>

<p>Serializing all the complex objects is done with <a href="http://www.boost.org/libs/serialization/doc/">Boost serialization</a>.</p>

<h2>License</h2>

<p>The library itself is licensed under <a href="http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html">LGPL 2.1</a> (not any later).</p>


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