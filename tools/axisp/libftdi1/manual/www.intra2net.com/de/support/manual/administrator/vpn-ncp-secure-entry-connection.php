<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Verbindungen | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-ncp-secure-entry.php" title="41. Kapitel - VPN mit dem NCP Secure Entry Client"><link rel="prev" href="vpn-ncp-secure-entry-certificates.php" title="41.2. Zertifikate"><link rel="next" href="vpn-ncp-secure-entry-intranator.php" title="41.4. Intranator">
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

<a href="vpn-ncp-secure-entry-connection.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-ncp-secure-entry-connection.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">41.3. Verbindungen</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-ncp-secure-entry-certificates.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">41. Kapitel - VPN mit dem NCP Secure Entry Client</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-ncp-secure-entry-intranator.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-ncp-secure-entry-connection"></a>41.3. Verbindungen</h2></div></div></div><div class="orderedlist"><ol type="1"><li><p>&Ouml;ffnen Sie den NCP Client Monitor, Men&uuml; <span class="guimenu">Konfiguration</span>,
            <span class="guimenuitem">Profil-Einstellungen</span>. Starten Sie &uuml;ber <span class="guibutton">Hinzuf&uuml;gen
            / Import</span> den Konfigurations-Wizard.</p></li><li><p>W&auml;hlen Sie eine IPSec-Verbindung</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz1.png"></div></li><li><p>Vergeben Sie einen Namen f&uuml;r die Verbindung</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz2.png"></div></li><li><p>Verwenden Sie die automatische Medienerkennung.</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz3.png"></div></li><li><p>Tragen Sie die (externe) IP oder den (Dyn-)DNS-Namen des Intranators als Gateway ein.
          Wenn Ihr Intranator &uuml;ber eine feste IP verf&uuml;gt, ist es besser diese einzutragen, anstatt
          den DNS-Namen zu verwenden. Lassen Sie XAUTH inaktiv.</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz4.png"></div></li><li><p>Verwenden Sie den "Main Mode" als Austausch-Modus und verwenden Sie die DH-Gruppe 5
          (1536 Bit) f&uuml;r PFS (Perfect Forward Secrecy).</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz5.png"></div></li><li><p>Lassen Sie die Einstellungen f&uuml;r Pre-shared Key leer und stellen den Typ der lokalen
          Identit&auml;t auf "ASN1 Distinguished Name". Dadurch werden die Daten aus dem Zertifikat zur
          Identifizierung &uuml;bertragen.</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz6.png"></div></li><li><p>Stellen Sie die IP-Adressen-Zuweisung auf "IKE Config Mode verwenden". Damit wird die
          virtuelle IP durch den Intranator zugewiesen. Lassen Sie die Felder f&uuml;r IP, DNS-Server und
          WINS-Server alle auf <strong class="userinput"><code>0.0.0.0</code></strong> stehen. So werden die durch den
          Intranator zugewiesenen Werte verwendet.</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz7.png"></div></li><li><p>Aktivieren Sie die Firewall des NCP Clients, indem Sie die Stateful Inspection auf
          "bei bestehender Verbindung" stellen.</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-wiz8.png"></div></li><li><p>Als n&auml;chstes m&uuml;ssen Sie dem Client mitteilen, bei dieser Verbindung das Zertifikat zur
          Authentifizierung zu verwenden. Markieren Sie in den Profil-Einstellungen die eben
          erzeugte VPN-Verbindung und klicken auf <span class="guibutton">Bearbeiten</span>. Im Men&uuml;punkt
            <span class="guimenu">Identit&auml;t</span> k&ouml;nnen Sie die Zertifikats-Authentifizierung aktivieren, indem 
          Sie die Option <span class="guilabel">Zertifikats-Konfiguration</span> auf <span class="guilabel">Standard
            PKI-Konfiguration</span> stellen.</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-identity.png"></div></li><li><p>Passen Sie nun die G&uuml;ltigkeitszeitspannen f&uuml;r die Verbindung an. &Ouml;ffnen Sie dazu den Reiter
          <span class="guimenu">IPSec-Einstellungen</span>, Schaltknopf <span class="guibutton">G&uuml;ltigkeit</span>.</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-lifetime1.png"></div><p>Eine optimale 
          Verbindungsstabilit&auml;t auch &uuml;ber l&auml;ngere Zeitr&auml;ume wird erreicht, wenn die G&uuml;ltigkeit f&uuml;r IPSec-Richtlinien
          auf dem Client etwas k&uuml;rzer eingestellt ist als auf dem Intranator. Stellen Sie daher die Dauer auf
          45 Minuten (auf dem Intranator wird standardm&auml;&szlig;ig 60 Minuten verwendet).</p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-lifetime2.png"></div></li><li><p>Als letztes m&uuml;ssen Sie noch das zu verbindende VPN-Netz konfigurieren. Im Men&uuml;punkt
            <span class="guimenu">Split Tunneling</span> k&ouml;nnen Sie das Netz hinter dem Intranator eintragen. </p><div class="mediaobject"><img src="../images/vpn/ncp/ncp-tunnel1.png"></div><div class="mediaobject"><img src="../images/vpn/ncp/ncp-tunnel2.png"></div><p>Wenn Sie mehr als ein Netz mit einem Intranator verbinden m&ouml;chten, k&ouml;nnen Sie auf
          Seite des NCP Clients mehrere Netze in dieses Men&uuml; eintragen. Auf dem Intranator m&uuml;ssen
          Sie hingegen mehrere separate Verbindungen konfigurieren.</p><p>Soll das VPN auch f&uuml;r den Internetzugang verwendet werden, tragen Sie hier kein Netz
          ein und stellen auf dem Intranator das Lokale Netz auf <strong class="userinput"><code>Alles
            (0.0.0.0/0.0.0.0)</code></strong>.</p></li></ol></div><a class="indexterm" name="d0e12502"></a><a class="indexterm" name="d0e12503"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-ncp-secure-entry-certificates.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-ncp-secure-entry.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-ncp-secure-entry-intranator.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">41.2. Zertifikate&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;41.4. Intranator</td></tr></table></div>
      
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