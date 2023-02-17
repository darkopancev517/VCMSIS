<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>VPN mit dem NetGear ProSafe Client | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn.php" title="Teil&nbsp;6.&nbsp;VPN"><link rel="prev" href="vpn-shrew-trace.php" title="42.5. Verbindungsprotokolle"><link rel="next" href="vpn-netgear-client-installation.php" title="43.2. Installation">
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

<a href="vpn-netgear-client.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-netgear-client.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">43. Kapitel - VPN mit dem NetGear ProSafe Client</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-shrew-trace.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;6.&nbsp;VPN</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-netgear-client-installation.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="vpn-netgear-client"></a>43. Kapitel - VPN mit dem NetGear ProSafe Client</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="vpn-netgear-client.php#vpn-netgear-client-compatibility">43.1. Kompatibilit&auml;t</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-installation.php">43.2. Installation</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-certificates.php">43.3. Zertifikate</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-connections.php">43.4. Verbindungen</a></span></dt><dt><span class="sect1"><a href="vpn-netgear-client-intranator.php">43.5. Intranator</a></span></dt></dl></div><a class="indexterm" name="vpn-netgear-client1"></a><a class="indexterm" name="vpn-netgear-client2"></a><a class="indexterm" name="vpn-netgear-client3"></a><p>Der Netgear <span class="productname">ProSafe VPN Client</span>&#8482; (Netgear-Artikelnr. VPN01L) und
    einige weitere VPN-Clients sind OEM-Versionen von (und damit vom Funktionsumfang identisch mit)
    SafeNet SoftRemote.</p><p>Diese Anleitung gilt nur f&uuml;r den <span class="productname">ProSafe VPN Client</span>&#8482; (Artikelnr.
    VPN01L). Der <span class="productname">ProSafe VPN Client Professional</span>&#8482; (Artikelnr. VPNG01L) ist
    ein vollkommen anderes Produkt und wird hier nicht beschrieben.</p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Intra2net r&auml;t, diesen Client nicht mehr f&uuml;r neue Installationen zu verwenden. Diese
      Dokumentation ist nur noch als Referenz f&uuml;r Bestandsinstallationen gedacht.</p></td></tr></table></div><p>Der Netgear <span class="productname">ProSafe VPN Client</span>&#8482; wird h&auml;ufig in einer &auml;lteren
    Version (Version 10.1 aus dem Jahre 2003) ausgeliefert. Bei diesen alten Versionen kann es
    vorkommen, dass sie sich nicht installieren lassen oder im Betrieb St&ouml;rungen auftreten (u.a. kann
    der virtuelle Adapter nicht angelegt werden). Wir empfehlen daher, immer von Anfang an eine
    aktuelle Version zu installieren.</p><p>Sollten Sie eine alte Version geliefert bekommen haben, k&ouml;nnen Sie vom Netgear-Support mit
    der Seriennummer (siehe Aufkleber auf dem Karton) eine aktuelle Version anfordern. Rufen Sie
    beim deutschen Netgear Support an und Sie bekommen erfahrungsgem&auml;&szlig; ohne gro&szlig;en Aufwand und
    zeitnah eine neue Version per E-Mail zugesendet.</p><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-netgear-client-compatibility"></a>43.1. Kompatibilit&auml;t</h2></div></div></div><p>Ab Version 10.8 wird Microsoft Windows Vista in der 32-Bit-Version unterst&uuml;tzt. Wenn Sie
      Windows 7 (32- und 64-Bit) oder die 64-Bit-Version von Vista einsetzen, empfehlen wir den NCP
      Secure Entry Client, beschrieben im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="vpn-ncp-secure-entry.php">41. Kapitel,&nbsp;&#8222;VPN mit dem NCP Secure Entry Client&#8220;</a>.</p><p>Stellen Sie sicher, dass auf dem Rechner keine weiteren VPN-Clients (z.B. von Cisco,
      Nortel, etc.) installiert sind. Es kann, bis auf ganz wenige Ausnahmen, immer nur eine
      VPN-Software auf einem Rechner installiert sein. </p><p>Stellen Sie sicher, dass auf dem Rechner keine &#8220;Netzwerk-Manager&#8221;-Software installiert ist.
      Diese versucht typischerweise auch ohne DHCP die Netzwerkkonfiguration automatisch an das
      aktuelle Netz anzupassen und wird vor allem von einigen Notebook-Herstellern bei der
      Auslieferung vorinstalliert. Diese Software klinkt sich in den meisten F&auml;llen in die
      Netzwerksteuerung von Windows ein und st&ouml;rt dabei die Funktion des VPN-Clients. Deinstallieren
      Sie den Netzwerk-Manager und starten den Rechner neu.</p><p>Von Kunden wurde berichtet, dass es mit bestimmten Versionen von TrendMicro-Produkten sowie
      ZoneAlarm zu Kompatibilit&auml;tsproblemen kommen kann. Diese &auml;u&szlig;ern sich darin, dass beim
      Verbindungsaufbau der virtuelle Adapter nicht angelegt werden kann. Verwenden Sie in diesem
      Fall ein anderes Client-Firewall-Produkt oder versuchen es mit einem anderen VPN-Client, wie
      z.B. dem NCP Secure Entry Client, beschrieben im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="vpn-ncp-secure-entry.php">41. Kapitel,&nbsp;&#8222;VPN mit dem NCP Secure Entry Client&#8220;</a>.</p></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-shrew-trace.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-netgear-client-installation.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">42.5. Verbindungsprotokolle&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;43.2. Installation</td></tr></table></div>
      
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