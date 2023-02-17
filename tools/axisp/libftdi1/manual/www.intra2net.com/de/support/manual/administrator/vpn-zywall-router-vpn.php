<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Konfiguration der VPN-Verbindung | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-zywall-router.php" title="50. Kapitel - VPN mit ZyXEL ZyWALL Routern"><link rel="prev" href="vpn-zywall-router-cert.php" title="50.4. Erzeugen und Installieren des Router-Zertifikats"><link rel="next" href="vpn-zywall-router-intranator.php" title="50.6. Intranator">
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

<a href="vpn-zywall-router-vpn.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-zywall-router-vpn.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">50.5. Konfiguration der VPN-Verbindung</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-zywall-router-cert.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">50. Kapitel - VPN mit ZyXEL ZyWALL Routern</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-zywall-router-intranator.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-zywall-router-vpn"></a>50.5. Konfiguration der VPN-Verbindung</h2></div></div></div><p>Als n&auml;chstes muss die VPN-Verbindung konfiguriert werden. Auf dem Router ist die
      Konfiguration nach den beiden Phasen des Verbindungsaufbaus aufgeteilt.</p><p>&Ouml;ffnen Sie das Men&uuml; Security &gt; VPN, Reiter VPN Rules (IKE) und klicken auf das
        <span class="guibutton">Add Gateway Policy</span> Symbol.</p><div class="mediaobject"><img src="../images/vpn/zywall-router/zywall-newrule.png"></div><p>Geben Sie der Verbindung einen Namen. Sollte der Intranator oder die Zywall hinter einem
      NAT-Router sein, m&uuml;ssen Sie die <span class="guilabel">NAT Traversal</span> Option aktivieren.</p><p>Unter <span class="guilabel">Gateway Policy Information</span> lassen Sie <span class="guilabel">My ZyWall / My
        Address</span> auf <strong class="userinput"><code>0.0.0.0</code></strong> stehen. Dies bedeutet, dass die
      Standard-Internet-IP der ZyWall verwendet wird.</p><p>Bei <span class="guilabel">Primary Remote Gateway</span> tragen Sie die externe IP (wenn vorhanden)
      oder den DNS-Namen des Intranators ein.</p><p>Bei <span class="guilabel">Authentication Key</span> aktivieren Sie
        <span class="guilabel">Certificate</span> und w&auml;hlen das eben erstellte Zertifikat der Zywall aus.
      Den <span class="guilabel">Peer ID Type</span> stellen Sie auf <span class="guimenuitem">Any</span>.</p><p><span class="guilabel">Extended Authentication</span> bleibt deaktiviert. Unter <span class="guilabel">IKE
        Proposal</span> stellen Sie den <span class="guilabel">Negotiation Mode</span> auf
        <span class="guimenuitem">Main</span>. <span class="guilabel">Encryption Algorithm</span>,
        <span class="guilabel">Authentication Algorithm</span> und <span class="guilabel">Key Group</span> (Entspricht
        <span class="guilabel">Diffie Hellman Gruppe</span> auf dem Intranator) m&uuml;ssen zu dem im Intranator
      gew&auml;hlten Verschl&uuml;sselungsprofil passen. Die Werte <span class="guimenuitem">AES</span>,
        <span class="guimenuitem">SHA1</span> und <span class="guimenuitem">DH2</span> sind mit dem
      Standardverschl&uuml;sselungsprofil des Intranators kompatibel.</p><div class="mediaobject"><img src="../images/vpn/zywall-router/zywall-gwpol.png"></div><p>Nach Erstellung der Verbindung erscheint wieder die &Uuml;bersichtsseite. Klicken Sie auf das
        <span class="guilabel">Add Network Policy</span> Symbol, um die zweite Phase der Verbindung zu
      konfigurieren.</p><div class="mediaobject"><img src="../images/vpn/zywall-router/zywall-ruleselect.png"></div><p>Aktivieren Sie die <span class="guilabel">Active</span> Checkbox und geben der Policy einen Namen.
      Soll die Verbindung st&auml;ndig aufgebaut bleiben, so aktivieren Sie zus&auml;tzlich
        <span class="guilabel">Nailed-Up</span>.</p><p>Im Block <span class="guilabel">Local Network</span> wird die lokale Seite des VPN-Tunnels
      konfiguriert. Stellen Sie den <span class="guilabel">Address Type</span> auf <span class="guimenuitem">Subnet
        Address</span> und stellen IP und Netzmaske des lokalen Netzes an der Zywall
      ein.</p><p>Im Block <span class="guilabel">Remote Network</span> wird mit Typ <span class="guimenuitem">Subnet
        Address</span> das Netz am Intranator eingestellt.</p><p>Im Block <span class="guilabel">IPSec Proposal</span> werden die Kapselungs- und
      Verschl&uuml;sselungsverfahren konfiguriert. Diese m&uuml;ssen zur Konfiguration der Verbindung auf dem
      Intranator passen. W&auml;hlen Sie bei <span class="guilabel">Encapsulation Mode</span> die Option
        <span class="guimenuitem">Tunnel</span>. Zur Standardkonfiguration des Intranators passen die
      Werte <span class="guimenuitem">ESP</span>, <span class="guimenuitem">AES</span>,
        <span class="guimenuitem">SHA1</span> und <span class="guimenuitem">DH2</span>.</p><div class="mediaobject"><img src="../images/vpn/zywall-router/zywall-netpol.png"></div><p>Jetzt ist die VPN-Verbindung fertig konfiguriert. In der Verbindungs&uuml;bersicht erscheint
      nun ein kleines Telefonsymbol. Klicken Sie auf dieses, um die Verbindung aufzubauen.</p><div class="mediaobject"><img src="../images/vpn/zywall-router/zywall-connect.png"></div><a class="indexterm" name="d0e15142"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-zywall-router-cert.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-zywall-router.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-zywall-router-intranator.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">50.4. Erzeugen und Installieren des Router-Zertifikats&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;50.6. Intranator</td></tr></table></div>
      
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