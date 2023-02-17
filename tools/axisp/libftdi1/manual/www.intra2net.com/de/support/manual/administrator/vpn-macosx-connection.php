<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Verbindungen konfigurieren | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-macosx.php" title="44. Kapitel - VPN mit Mac OS X"><link rel="prev" href="vpn-macosx-cert-import.php" title="44.3. Zertifikate importieren"><link rel="next" href="vpn-macosx-intranator.php" title="44.5. Intranator">
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

<a href="vpn-macosx-connection.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-macosx-connection.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">44.4. Verbindungen konfigurieren</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-macosx-cert-import.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">44. Kapitel - VPN mit Mac OS X</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-macosx-intranator.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-macosx-connection"></a>44.4. Verbindungen konfigurieren</h2></div></div></div><div class="orderedlist"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml; <span class="guimenu">Connections</span>, <span class="guisubmenu">Edit
            connections</span> in <span class="application">IPSecuritas</span>.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_empty.png"></div></li><li><p>Legen Sie &uuml;ber das <span class="guibutton">New</span>-Symbol eine neue Verbindung an und geben
          ihr einen Namen (in diesem Beispiel <strong class="userinput"><code>Intranator</code></strong>).</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_new.png"></div></li><li><p>Im Men&uuml; <span class="guimenu">General</span> tragen Sie unter <span class="guimenuitem">Remote IPSec
            Device</span> die (offizielle) IP oder den DNS-Namen der Gegenstelle ein.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_general.png"></div></li><li><p>Stellen Sie bei <span class="guilabel">Local Side</span> den <span class="guimenuitem">Endpoint
            Mode</span> auf <span class="guimenuitem">Host</span> und geben die virtuelle IP ein,
          die der Mac-Client innerhalb des VPNs verwenden soll.</p></li><li><p>Stellen Sie bei <span class="guilabel">Remote Side</span> den <span class="guimenuitem">Endpoint
            Mode</span> auf <span class="guimenuitem">Network</span> und geben die Adresse des
          Netzes hinter dem Intranator ein. Die Netzmaske wird in CIDR-Notation eingegeben;
            <strong class="userinput"><code>24</code></strong> (Bit) entspricht <strong class="userinput"><code>255.255.255.0</code></strong>.</p></li><li><p>Im Men&uuml; <span class="guimenu">Phase 1</span> k&ouml;nnen Sie die Verschl&uuml;sselungsparameter f&uuml;r
          Phase 1 konfigurieren. Diese m&uuml;ssen zum auf dem Intranator gew&auml;hlten
          Verschl&uuml;sselungsprofil passen.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_phase1.png"></div></li><li><p>Im Men&uuml; <span class="guimenu">Phase 2</span> k&ouml;nnen Sie die Verschl&uuml;sselungsparameter f&uuml;r
          Phase 2 konfigurieren. Diese m&uuml;ssen zum auf dem Intranator gew&auml;hlten
          Verschl&uuml;sselungsprofil passen.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_phase2.png"></div></li><li><p>Stellen Sie im Men&uuml; <span class="guimenu">ID</span> bei <span class="guimenuitem">Local
            Identifier</span> und <span class="guimenuitem">Remote Identifier</span> jeweils
            <span class="guimenuitem">Certificate</span> ein. W&auml;hlen Sie
            <span class="guimenuitem">Certificates</span> als <span class="guimenuitem">Authentication
            Method</span> und stellen die beiden vorher importierten Zertifikate ein.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_id.png"></div></li><li><p>Im Men&uuml; <span class="guimenu">DNS</span> haben Sie die M&ouml;glichkeit, eine bestimmte Domain von
          einem Server im VPN (z.B. dem Intranator) aufl&ouml;sen zu lassen.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_dns.png"></div></li><li><p>Stellen Sie im Men&uuml; <span class="guimenu">Options</span> die verschiedenen Optionen so ein, wie
          hier gezeigt.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_options.png"></div></li><li><p>Nun k&ouml;nnen Sie im Hauptfenster die Verbindung &uuml;ber den
          <span class="guibutton">Start</span>-Knopf aufbauen.</p><div class="mediaobject"><img src="../images/vpn/macosx/conn_start.png"></div></li></ol></div><a class="indexterm" name="d0e13392"></a><a class="indexterm" name="d0e13393"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-macosx-cert-import.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-macosx.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-macosx-intranator.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">44.3. Zertifikate importieren&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;44.5. Intranator</td></tr></table></div>
      
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