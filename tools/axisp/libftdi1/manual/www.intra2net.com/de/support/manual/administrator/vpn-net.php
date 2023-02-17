<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Anbinden von kompletten Netzen | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn.php" title="Teil&nbsp;6.&nbsp;VPN"><link rel="prev" href="vpn-ncp-symbian-intranator.php" title="48.4. Intranator"><link rel="next" href="vpn-net-intranator.php" title="49.2. Konfiguration auf dem Intranator">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn-net.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-net.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">49. Kapitel - Anbinden von kompletten Netzen</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-ncp-symbian-intranator.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;6.&nbsp;VPN</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-net-intranator.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="vpn-net"></a>49. Kapitel - Anbinden von kompletten Netzen</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="vpn-net.php#vpn-net-concept">49.1. Konzept</a></span></dt><dt><span class="sect1"><a href="vpn-net-intranator.php">49.2. Konfiguration auf dem Intranator</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-prereq">49.2.1. Voraussetzungen</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-basicconfig">49.2.2. Grundeinstellungen</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-auth">49.2.3. Authentifizierung</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-tunnel">49.2.4. Tunnel konfigurieren</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-rights">49.2.5. Rechte</a></span></dt><dt><span class="sect2"><a href="vpn-net-intranator.php#vpn-net-intranator-activation">49.2.6. Aktivierung</a></span></dt></dl></dd></dl></div><a class="indexterm" name="vpn-net1"></a><a class="indexterm" name="vpn-net2"></a><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-net-concept"></a>49.1. Konzept</h2></div></div></div><p>Wenn in einem entfernten Netz mehrere Rechner mit einem Netz hinter dem Intranator
      verbunden werden sollen (z.B. in einer Filiale), ist es normalerweise sinnvoller, ein VPN
      zwischen den beiden Netzen aufzubauen anstatt f&uuml;r jeden dieser Rechner ein einzelnes
      VPN.</p><p>Dieses VPN wird dann zwischen dem Intranator und einem IPSec Gateway vor dem anderen Netz
      aufgebaut. Dieses IPSec Gateway kann ein Intranator sein, es kann sich aber auch um ein anderes
      kompatibles Produkt handeln.</p><div class="mediaobject"><img src="../images/vpn/conn-LAN-LAN.png"></div><p>&Uuml;ber einen VPN-Tunnel k&ouml;nnen auch Netze mit privaten IPs verbunden werden. Die IPs dienen
      aber weiterhin zur Adressierung. Daher k&ouml;nnen Sie keine Netze mit identischen oder
      &uuml;berlappenden Netzbereichen per VPN verbinden.</p><p>Achten Sie darauf, dass der Intranator und das IPSec Gateway auf der Gegenstelle selbst
      eine offizielle IP bekommen und nicht hinter einem Router stehen, der NAT macht. VPN hinter
      einem NAT-Router ist zwar m&ouml;glich, kann jedoch vor allem dann zu Schwierigkeiten f&uuml;hren, wenn
      beide Seiten hinter NAT-Routern sind.</p><a class="indexterm" name="vpn-net-dynamicip1"></a><a class="indexterm" name="vpn-net-dynamicip2"></a><p>Es ist nicht notwendig, fest zugewiesene IPs zu verwenden, es k&ouml;nnen ohne Schwierigkeiten
      auf einer oder beiden Seiten dynamische IPs mit DynDNS zum Einsatz kommen.</p><p>Wenn die Verbindung auf einer Seite regelm&auml;&szlig;ig getrennt wird (z.B. durch Zwangstrennung
      bei DSL), sollten Sie daf&uuml;r sorgen, dass die Verbindung von beiden Seiten her aufgebaut werden
      kann und nicht nur von einer.</p><a class="indexterm" name="d0e14796"></a><a class="indexterm" name="d0e14797"></a><p>Eine auf dem Intranator konfigurierte Verbindung gilt f&uuml;r die Verbindung von einem Netz
      auf Seite der Gegenstelle und einem Netz hinter dem Intranator. M&ouml;chten Sie mehrere Netze
      miteinander verbinden, k&ouml;nnen Sie f&uuml;r jede Netzkombination eine eigene Verbindung
      konfigurieren. Achten Sie darauf, f&uuml;r jede dieser Verbindungen immer dieselbe Kombination an
      Schl&uuml;sseln/Zertifikaten zu verwenden.</p></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-ncp-symbian-intranator.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-net-intranator.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">48.4. Intranator&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;49.2. Konfiguration auf dem Intranator</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
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

    </body></html>