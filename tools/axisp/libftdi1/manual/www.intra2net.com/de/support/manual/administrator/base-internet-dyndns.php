<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>DynDNS | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-internet.php" title="11. Kapitel - Internet"><link rel="prev" href="base-internet-wakeup-call.php" title="11.11. Lockruf"><link rel="next" href="base-internet-external-access.php" title="11.13. Zugriff von au&szlig;en">
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

<a href="base-internet-dyndns.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-internet-dyndns.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">11.12. DynDNS</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-internet-wakeup-call.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">11. Kapitel - Internet</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-internet-external-access.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-internet-dyndns"></a>11.12. DynDNS</h2></div></div></div><a class="indexterm" name="base-internet-dyndns1"></a><p>Damit der Intranator trotz wechselnder IP Adressen z.B. f&uuml;r VPN oder externen
      HTTPS-Zugriff &uuml;ber das Internet erreichbar bleiben kann, kann der Intranator seine IP Adresse
      &uuml;ber DynDNS-Dienste bekanntgeben. Dabei teilt der Intranator seine neue IP nach jeder Einwahl
      einem DynDNS-Anbieter mit. &Uuml;ber einen normalen DNS-Namen wie z.B. intranator.dyndns.org kann
      man dann auf den Intranator unter seiner momentan verwendeten externen IP zugreifen.</p><p>Unter Dienste&nbsp;&gt;&nbsp;DynDNS k&ouml;nnen Sie mehrere Konten bei
      verschiedenen DynDNS-Anbietern konfigurieren.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-internet-dyndns-provider"></a>11.12.1. Anbieter</h3></div></div></div><p>Folgende DynDNS-Dienste werden momentan vom Intranator unterst&uuml;tzt:</p><div class="informaltable"><table border="1"><colgroup><col align="left"><col align="left"><col align="left"></colgroup><thead><tr><th align="left">Anbieter</th><th align="left">Preis</th><th align="left">Einstellungen im Intranator</th></tr></thead><tbody><tr><td align="left">
                  <a class="ulink" href="http://www.no-ip.com/" target="_top">No-IP</a>
                </td><td align="left">Kostenlos (bis 5 Eintr&auml;ge)</td><td align="left">
                  <div class="itemizedlist"><ul type="disc"><li><p>Protokoll: dyndns</p></li><li><p>Alternativer Server: dynupdate.no-ip.com</p></li></ul></div>
                </td></tr><tr><td align="left">
                  <a class="ulink" href="http://www.dnsdynamic.org/" target="_top">DNSdynamic</a>
                </td><td align="left">Kostenlos</td><td align="left">
                  <div class="itemizedlist"><ul type="disc"><li><p>Protokoll: dyndns</p></li><li><p>Alternativer Server: www.dnsdynamic.org</p></li></ul></div>
                </td></tr><tr><td align="left">
                  <a class="ulink" href="http://www.changeip.com/" target="_top">ChangeIP.com</a>
                </td><td align="left">Kostenlos</td><td align="left">
                  <div class="itemizedlist"><ul type="disc"><li><p>Protokoll: dyndns</p></li><li><p>Alternativer Server: nic.changeip.com</p></li></ul></div>
                </td></tr><tr><td align="left">
                  <a class="ulink" href="http://www.dyns.cx/" target="_top">DyNS</a>
                </td><td align="left">5 US$ einmalig</td><td align="left">
                  <div class="itemizedlist"><ul type="disc"><li><p>Protokoll: dyns</p></li></ul></div>
                </td></tr><tr><td align="left">
                  <a class="ulink" href="http://www.dyn.com/dns/" target="_top">Dyn</a>
                </td><td align="left">25 US$ / Jahr</td><td align="left">
                  <div class="itemizedlist"><ul type="disc"><li><p>Protokoll: dyndns</p></li></ul></div>
                </td></tr><tr><td align="left">
                  <a class="ulink" href="http://www.dyndnsfree.de/" target="_top">Namemaster</a>
                </td><td align="left">12 &#8364; / Jahr</td><td align="left">
                  <div class="itemizedlist"><ul type="disc"><li><p>Protokoll: dyndns</p></li><li><p>Alternativer Server: dynup.de</p></li></ul></div>
                </td></tr><tr><td align="left">
                  <a class="ulink" href="http://www.dhs.org/" target="_top">DHS</a>
                </td><td align="left">5 US$ / Jahr</td><td align="left">
                  <div class="itemizedlist"><ul type="disc"><li><p>Protokoll: dhs</p></li></ul></div>
                </td></tr></tbody></table></div><p>Alle Angaben ohne Gew&auml;hr.</p><p>Hier finden Sie eine umfangreiche <a class="ulink" href="http://dnslookup.me/dynamic-dns/" target="_top">Liste
          mit weiteren DynDNS-Anbietern</a>. Wir k&ouml;nnen allerdings nicht garantieren, dass diese
        Anbieter alle mit dem Intranator kompatibel sind.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-internet-dyndns-update"></a>11.12.2. Aktualisierung und verwendete IP</h3></div></div></div><p>F&uuml;r jeden Internetprovider kann unter
        Netzwerk&nbsp;&gt;&nbsp;Provider&nbsp;&gt;&nbsp;Profile&nbsp;:&nbsp;Dienste
        eingestellt werden, ob bei einer Einwahl die DynDNS-Dienste (es k&ouml;nnen zur Sicherheit
        mehrere gleichzeitig konfiguriert werden) aktualisiert werden sollen. </p><p>Die verwendete IP Adresse, ist normalerweise die externe IP des Intranators. Es kann
        aber vorkommen, dass eine Verbindung mehrfach NAT durchl&auml;uft und im Internet daher eine
        andere Adresse bekannt gegeben werden soll. Dies kann &uuml;ber die Einstellung &#8222;DynDNS IP von
        Webseite holen&#8220; konfiguriert werden. Der Intranator fragt dann vorher einen Webserver nach
        der IP, von der die Anfrage kommt, und &uuml;bermittelt diese dann an den DynDNS-Server.</p><a class="indexterm" name="d0e2752"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-internet-wakeup-call.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-internet.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-internet-external-access.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">11.11. Lockruf&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;11.13. Zugriff von au&szlig;en</td></tr></table></div>
      
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